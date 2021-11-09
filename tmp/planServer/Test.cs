using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TSocket
{ 
    public class MarshalEndian
    {
        //用于存储剩余未解析的字节数
        private List<byte> _LBuff = new List<byte>(2);
        //默认是utf8的编码格式
        private UTF8Encoding utf8 = new UTF8Encoding();

        //包头1
        const Int16 t1 = 0x55;
        //包头2
        const Int16 t2 = 0xAA;
        //字节数常量 两个包头4个字节，一个消息id4个字节，封装消息长度 int32 4个字节
        const Int32 ConstLenght = 8;

        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool flag1)
        {
            if (flag1)
            {
                IDisposable disposable2 = this.utf8 as IDisposable;
                if (disposable2 != null) { disposable2.Dispose(); }
                IDisposable disposable = this._LBuff as IDisposable;
                if (disposable != null) { disposable.Dispose(); }
            }
        }

        public byte[] Encode(TSocketMessage msg)
        {
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms, new UTF8Encoding());
            byte[] msgBuffer = msg.MsgBuffer;

            #region 封装包头
            bw.Write((Int16) t1);
            bw.Write((Int16) t2);
            #endregion

            #region 包协议
            if (msgBuffer != null)
            {
                bw.Write((Int32)(msgBuffer.Length + 4));
                bw.Write(msg.MsgID);
                bw.Write(msgBuffer);
            }
            else { bw.Write((Int32)0); }
            #endregion

            bw.Close();
            ms.Close();
            bw.Dispose();
            ms.Dispose();
            return ms.ToArray();
        }

        public List<TSocketMessage> GetDcAppMess(byte[] buff, int len)
        {
            //拷贝本次的有效字节
            byte[] _b = new byte[len];
            Array.Copy(buff, 0, _b, 0, _b.Length);
            buff = _b;
            if (this._LBuff.Count > 0)
            {
                //拷贝之前遗留的字节
             this._LBuff.AddRange(_b);
                buff = this._LBuff.ToArray();
                this._LBuff.Clear();
                this._LBuff = new List<byte>(2);
            }

            List<TSocketMessage> list = new List<TSocketMessage>();
            MemoryStream ms = new MemoryStream(buff);
            BinaryReader buffers = new BinaryReader(ms, this.utf8);
            try
            {
                byte[] _buff;
            Label_00983:

                #region 包头读取
                //循环读取包头           
                //判断本次解析的字节是否满足常量字节数 
                if ((buffers.BaseStream.Length - buffers.BaseStream.Position) < ConstLenght)
                {
                    _buff = buffers.ReadBytes((int)(buffers.BaseStream.Length - buffers.BaseStream.Position));
                    this._LBuff.AddRange(_buff);
                    return list;
                 }
                 Int16 tt1 = buffers.ReadInt16();
                 Int16 tt2 = buffers.ReadInt16();
                 if (!(tt1 == t1 && tt2 == t2))
                 {
                     long ttttt = buffers.BaseStream.Seek(-3, SeekOrigin.Current);
                     goto Label_00983;
                 }
                 #endregion
 
                 #region 包协议
                 int offset = buffers.ReadInt32();
                 #endregion
 
                 #region 包解析
                 //剩余字节数大于本次需要读取的字节数
                 if (offset <= (buffers.BaseStream.Length - buffers.BaseStream.Position))
                 {
                     int msgID = buffers.ReadInt32();
                     _buff = buffers.ReadBytes(offset - 4);
                     list.Add(new TSocketMessage(msgID, _buff));
                     if ((buffers.BaseStream.Length - buffers.BaseStream.Position) > 0)
                     {
                         goto Label_00983;
                     }
                 }
                 else
                 {
                     //剩余字节数刚好小于本次读取的字节数 存起来，等待接受剩余字节数一起解析
                     _buff = buffers.ReadBytes((int)(buffers.BaseStream.Length - buffers.BaseStream.Position + ConstLenght));
                     this._LBuff.AddRange(_buff);
                 }
                 #endregion
             }
             catch (Exception ex) { Console.WriteLine(ex); }
             finally
             {
                 if (buffers != null) { buffers.Dispose(); }
                 buffers.Close();
                 if (buffers != null) { buffers.Dispose(); }
                 ms.Close();
                 if (ms != null) { ms.Dispose(); }
             }
             return list;
         }
     }
 }
    