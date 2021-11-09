using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace asyncSocket
{
    class MessageHandle
    {
        public static byte[] StructToBytes(object structObj, int size)
        {
            byte[] bytes = new byte[size];
            IntPtr structPtr = Marshal.AllocHGlobal(size);
            //将结构体拷到分配好的内存空间
            Marshal.StructureToPtr(structObj, structPtr, false);
            //从内存空间拷贝到byte 数组
            Marshal.Copy(structPtr, bytes, 0, size);
            //释放内存空间
            Marshal.FreeHGlobal(structPtr);
            return bytes;

        }

        //将Byte转换为结构体类型
        public static object ByteToStruct(byte[] bytes, Type type)
        {
            int size = Marshal.SizeOf(type);
            if (size > bytes.Length)
            {
                return null;
            }
            //分配结构体内存空间
            IntPtr structPtr = Marshal.AllocHGlobal(size);
            //将byte数组拷贝到分配好的内存空间
            Marshal.Copy(bytes, 0, structPtr, size);
            //将内存空间转换为目标结构体
            object obj = Marshal.PtrToStructure(structPtr, type);
            //释放内存空间
            Marshal.FreeHGlobal(structPtr);
            return obj;
        }

        public static int CheckAccount(string account)
        {
            if (!(6 <= account.Length && account.Length <= 16))
            {
                return 1; //长度不对
            }

            if (!System.Text.RegularExpressions.Regex.IsMatch(account, @"^[a-zA-Z][a-zA-Z0-9]{5,15}$"))
            {
                return 2;//必须字母开头,字母数字组成
            }

            return 0;
        }

        public static int CheckPassWord(string passWord)
        {
            if (!(8 <= passWord.Length && passWord.Length <= 16))
            {
                return 1; //长度不对
            }
            
            return 0;
        }

        static public void ProcessMsg(TSocketMessage msg, bool isServer, TSocketBase socket)
        {
          //  if (isServer)
            {       
                switch(msg.MsgID)
                {
                    case 1:
                        {
                            RegPacketTypeRes resPacket = new RegPacketTypeRes(0);
                            RegPacketType regInfo = (RegPacketType)ByteToStruct(msg.MsgBuffer, typeof(RegPacketType));
                            do
                            {
                                int cRes = CheckAccount(regInfo.account);
                                if (cRes != 0)
                                {
                                    resPacket.res = 1;
                                    break;
                                }

                                cRes = CheckPassWord(regInfo.passWord);
                                if (cRes != 0)
                                {
                                    resPacket.res = 3;
                                    break;
                                }

                                try
                                {
                                    string strSql = string.Format("select `account_id` from `plane_game`.`account` where `account_name`  like '{0}'", regInfo.account);
                                    MySqlCommand myCommand = Program.gSql.GetSqlCommand(strSql);
                                    MySqlDataReader read = Program.gSql.getReader(myCommand);
                                    if (read.HasRows)
                                    {
                                        resPacket.res = 2;
                                        myCommand.Cancel();
                                        read.Close();
                                        myCommand.Dispose();
                                        break;
                                    }
                                    myCommand.Cancel();
                                    read.Close();

                                    strSql = string.Format("INSERT INTO `plane_game`.`account` (`account_name`, `password`, `recharge`, `tel`) " +
                                        "VALUES ('{0}', '{1}', 0, '{2}')", regInfo.account, regInfo.passWord, regInfo.tel);
                                    myCommand.CommandText = strSql;
                                    int res = Program.gSql.Query(myCommand);
                                    
                                    if (res != 0)
                                    {
                                        resPacket.res = 100;
                                        break;
                                    }
                                }
                                catch(Exception ex)
                                {
                                    string log = string.Format("err:  msg {0}, {1}", msg.MsgID, ex.ToString());
                                    Program.WriteLog(log);
                                }
                            } while (false);

                           
                            Console.WriteLine("--Receive ID：" + msg.MsgID + ", res = " + resPacket.res);
                            int size = Marshal.SizeOf(resPacket);
                            socket.SendMsg(new TSocketMessage(msg.MsgID, StructToBytes(resPacket, size)));
                        }
                        break;
                    case 2:
                        {
                            LoginPacketTypeRes resPacket = new LoginPacketTypeRes(0);
                            LoginPacketType loginInfo = (LoginPacketType)ByteToStruct(msg.MsgBuffer, typeof(LoginPacketType));
                            do
                            {
                                int cRes = CheckAccount(loginInfo.account);
                                if (cRes != 0)
                                {
                                    resPacket.res = 1;
                                    break;
                                }

                                cRes = CheckPassWord(loginInfo.passWord);
                                if (cRes != 0)
                                {
                                    resPacket.res = 3;
                                    break;
                                }

                                string strSql = string.Format("select `password` from `plane_game`.`account` where account_name='{0}'", loginInfo.account);
                                MySqlCommand myCommand = Program.gSql.GetSqlCommand(strSql);
                                MySqlDataReader read = Program.gSql.getReader(myCommand);

                                try
                                {
                                    if (read.Read())
                                    {
                                        //int day = Convert.ToInt32(read["列名5"]);
                                        //reader.GetString(1)
                                        string tmpPassWord = read["password"].ToString();
                                        if (loginInfo.passWord != tmpPassWord)
                                        {
                                            resPacket.res = 3;
                                        }
                                        read.Close();
                                        myCommand.Dispose();
                                        break;
                                    }

                                    resPacket.res = 1;
                                    read.Close();
                                    myCommand.Dispose();
                                }
                                catch (Exception ex)
                                {
                                    string log = string.Format("sql read err : {0}", ex.ToString());
                                    Program.WriteLog(log);
                                    resPacket.res = 1;
                                    read.Close();
                                    myCommand.Dispose();
                                    break;
                                }

                            } while (false);

                            if (resPacket.res == 0)
                            {
                                socket.AccountName = loginInfo.account;
                            }
                            Console.WriteLine("--Receive ID：account = " + loginInfo.account + ", " + msg.MsgID + ", res = " + resPacket.res);
                            int size = Marshal.SizeOf(resPacket);
                            socket.SendMsg(new TSocketMessage(msg.MsgID, StructToBytes(resPacket, size)));
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
