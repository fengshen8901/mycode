using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace planeSve
{
    class Client
    {
        private Socket clientSocket;
        private Thread t;
        private byte[] data = new byte[1024];
        public bool Connected
        {
            get { return clientSocket.Connected; }
        }

        public Client(Socket s)
        {
            clientSocket = s;
            t = new Thread(ReceiveMessage);
            t.Start();
        }

        private void ReceiveMessage()
        {
            while(true)
            {
                if(clientSocket.Poll(10, SelectMode.SelectRead))
                {
                    clientSocket.Close();
                    break;
                }
                int len = clientSocket.Receive(data);
                string msg = Encoding.UTF8.GetString(data, 0, len);
                Console.WriteLine(msg);
                Program.BroadcastMessage(msg);
            }
        }

        public void SendMessage(string msg)
        {
            byte[] data = Encoding.UTF8.GetBytes(msg);

            int len = clientSocket.Send(data);
        }
    }
}
