using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace asyncSocket
{
    public class TSocketClient : TSocketBase
    {
        /// <summary>
        /// 是否是服务器端的资源
        /// </summary>
        private bool isServer = false;

        /// <summary>
        /// 客户端主动请求服务器
        /// </summary>
        /// <param name="ip"></param>
        /// <param name="port"></param>
        public TSocketClient(string ip = "127.0.0.1", int port = 9527)
        {
            isServer = false;
            this._Socket = new System.Net.Sockets.Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            this._Socket.Connect(ip, port);
            this.SetSocket();
            this.ReceiveAsync();
        }

        /// <summary>
        /// 这个是服务器收到有效链接初始化
        /// </summary>
        /// <param name="socket"></param>
        public TSocketClient(Socket socket)
        {
            isServer = true;
            this._Socket = socket;
            this.SetSocket();
            this.ReceiveAsync();
        }

        ///// <summary>
        ///// 收到消息后
        ///// </summary>
        ///// <param name="rbuff"></param>
        //public override void Receive(byte[] rbuff)
        //{
        //    Console.WriteLine("Receive Msg：" + System.Text.UTF8Encoding.Default.GetString(rbuff));
        //    if (isServer)
        //    {
        //        this.SendMsg(System.Text.UTF8Encoding.Default.GetBytes("Holle Client！"));
        //    }
        //}

        /// <summary>
        /// 收到消息后
        /// </summary>
        /// <param name="rbuff"></param>
        public override void Receive(TSocketMessage msg)
        {
            //Console.WriteLine("Receive threadId：" + Thread.CurrentThread.ManagedThreadId.ToString());
            //Console.WriteLine("Receive ID：" + msg.MsgID + " Msg：" + System.Text.UTF8Encoding.Default.GetString(msg.MsgBuffer));

            MessageHandle.ProcessMsg(msg, isServer, this);
            //if (isServer)
            //{
            //    this.SendMsg(new TSocketMessage(msg.MsgID, System.Text.UTF8Encoding.Default.GetBytes("Holle Client！")));
            //}
        }
    }
}
