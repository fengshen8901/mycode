using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Text;
using MySql.Data.MySqlClient;

namespace asyncSocket
{
    public class SqlHandle
    {
        private MySqlConnection myConnnect;
        public SqlHandle()
        {
            try
            {
                string ip = ConfigHelper.GetCustomSettings("sql", "ip");
                string user = ConfigHelper.GetCustomSettings("sql", "user");
                string password = ConfigHelper.GetCustomSettings("sql", "password");
                string dbName = ConfigHelper.GetCustomSettings("sql", "dbName");
                string constructorString = string.Format("server={0};User Id={1};password={2};Database={3}",
                                                                                               ip, user, password, dbName);
                myConnnect = new MySqlConnection(constructorString);
                myConnnect.Open();
                KeepConnect();
                Console.WriteLine("sql connect successes!");
            }
            catch (Exception ex)
            {
                string log = string.Format("sql connect err : {0}", ex.ToString());
                Program.WriteLog(log);
            }
        }

        public MySqlCommand GetSqlCommand(string sql)
        {
            //myConnnect.Open();
            MySqlCommand mySqlCommand = new MySqlCommand(sql, myConnnect);
            return mySqlCommand;
        }

        public MySqlDataReader getReader(MySqlCommand mySqlCommand)
        {
            Console.WriteLine("sql query select");
            return mySqlCommand.ExecuteReader();  
        }

        public int Query(MySqlCommand mySqlCommand)
        {
            try
            {
                Console.WriteLine("sql query");
                if (mySqlCommand.ExecuteNonQuery() > 0)
                {
                    mySqlCommand.Dispose();
                    Console.WriteLine("sql query successes! ");
                }
            }
            catch(Exception ex)
            {
                mySqlCommand.Dispose();
                string log = string.Format("sql query err : {0}", ex.ToString());
                Program.WriteLog(log);
                return 1;
            }
            return 0;
        }

        public void Dispose()
        {
            myConnnect.Close();
            GC.SuppressFinalize(this);
        }

        void KeepConnect()
        {
            int interval = ConfigHelper.GetCustomSettingsInt("sql", "keepTimer");
            System.Timers.Timer timer = new System.Timers.Timer();
            timer.Enabled = true;
            timer.Interval = (double)interval;
            timer.Start();
            timer.Elapsed += new System.Timers.ElapsedEventHandler(KeepSql);
        }

        void KeepSql(object sender, System.Timers.ElapsedEventArgs e)
        {
            int intHour = e.SignalTime.Hour;
            int intMinute = e.SignalTime.Minute;
            int intSecond = e.SignalTime.Second;

            try
            {
                string strSql = string.Format("select `account_id` from `plane_game`.`account` limit 1");
                MySqlCommand myCommand = GetSqlCommand(strSql);
                MySqlDataReader read = getReader(myCommand);

                myCommand.Cancel();
                read.Close();
                myCommand.Dispose();
            }
            catch(Exception ex)
            {
                string log = string.Format("keepSql err: {0}", ex.ToString());
                Program.WriteLog(log);                
            }
        }
    }
}
