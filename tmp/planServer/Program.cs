using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;

namespace planeSve
{
    class Program
    {
        static List<Client> clientList = new List<Client>();
        static void Main(string[] args)
        {
            //创建socket
            Socket tcpServer = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            EndPoint point = new IPEndPoint(IPAddress.Any, 10001);
            try
            {
                //绑定端口
                tcpServer.Bind(point);
                //监听 最大连接
                tcpServer.Listen(100);
                Console.WriteLine("start accept...");
                while (true)
                {
                    //接收连接  阻塞
                    Socket clientSocket = tcpServer.Accept();
                    Client client = new Client(clientSocket);
                    clientList.Add(client);
                }
                //string msg = "connect success";
                //byte[] data = Encoding.UTF8.GetBytes(msg);
                //int len = sClient.Send(data);
                //Console.WriteLine("sendlen = " + len);
            }
            catch (SocketException e)
            {
                Console.WriteLine(e.Message);
            }
            Console.ReadKey();
        }

        static public void BroadcastMessage(string msg)
        {
            var tmpList = new List<Client>();
            foreach (var client in clientList)
            {
                if (client.Connected)
                {
                    client.SendMessage(msg);
                }
                else
                {
                    tmpList.Add(client);
                }
            }

            foreach (var tmpClient in tmpList)
            {
                clientList.Remove(tmpClient);
            }
        }

        static public void Test()
        {
            string constructorString = "server=localhost;User Id=root;password=123456;Database=plane_game";
            MySqlConnection myConnnect = new MySqlConnection(constructorString);
            myConnnect.Open();
            MySqlCommand myCmd = new MySqlCommand("insert into account(account,password,recharge,tel) values('user001','123456',100,'18273282850'）", myConnnect);
            Console.WriteLine(myCmd.CommandText);
            if (myCmd.ExecuteNonQuery() > 0)
            {
                Console.WriteLine("数据插入成功！");
            }
            myCmd.CommandText = "update account set password=456789 where account_id=0";
            Console.WriteLine(myCmd.CommandText);
            if (myCmd.ExecuteNonQuery() > 0)
            {
                Console.WriteLine("数据更新成功！");
            }
            //myCmd.CommandText = "delete from t_dept";
            //Console.WriteLine(myCmd.CommandText);
            //if (myCmd.ExecuteNonQuery() > 0)
            //{
            //    Console.WriteLine("user表类型数据全部删除成功！");
            //}
            myCmd.Dispose();
            myConnnect.Close();
        }
    }
}
