using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace asyncSocket
{
    class Program
    {
        static TCPListener tcp;
        public static SqlHandle gSql;
        static void Main(string[] args)
        {
            Console.WriteLine("game start");
            WriteLog("start");
            WriteLog("end");
            gSql = new SqlHandle();

            Thread t = new Thread(StartListener);
            t.Start();

            int timer = 0;
            int space = 1000 / 60;
            while (true)
            {
                int nowTime = DateTime.Now.Millisecond;
                if (nowTime < timer)
                {
                    Thread.Sleep(timer - nowTime);
                }
                timer = DateTime.Now.Millisecond + space;
                if (tcp != null)
                    tcp.Update();
            }
           
            // t.Join();
            
            Console.ReadLine();
        }

        static public  void StartListener()
        {
            string ip = ConfigHelper.GetCustomSettings("socket", "ip");
            Console.WriteLine(ip);
            int port = ConfigHelper.GetCustomSettingsInt("socket", "port");
            tcp = new TCPListener(ip, port);
        }

        static public void WriteLog(string log)
        {
            Console.WriteLine(log);
            string folder = string.Format(@".\{0}-{1}", DateTime.Now.ToString("yyyy"), DateTime.Now.ToString("MM"));
            //判断文件夹是否存在
            if (!Directory.Exists(folder))
            {
                Directory.CreateDirectory(folder);
            }
            try
            {
                //File.WriteAllText(string.Format("{0}\\{1}.txt", folder, DateTime.Now.ToString("yyyyMMdd")), "测试信息向文件中覆盖写入信息", Encoding.UTF8);

                //在将文本写入文件前，处理文本行
                //StreamWriter 一个参数默认覆盖
                //StreamWriter 第二个参数为false覆盖现有文件，为true则把文本追加到文件末尾
                using (StreamWriter file = new StreamWriter(string.Format("{0}\\{1}.txt", folder, DateTime.Now.ToString("dd")), true))
                {
                    file.WriteLine(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + "  " + log);//直接追加文件末尾，不换行
                    file.WriteLine("---------------------------------");
                    file.WriteLine();// 直接追加文件末尾，换行
                    file.Close();
                }
            }
            catch (Exception)
            {
                throw;
            }
        }
    }
}
