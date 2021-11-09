using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace asyncSocket
{
    class ConfigHelper
    {
        private static IConfigurationRoot builder = null;
        static ConfigHelper()
        {
            builder = new ConfigurationBuilder()
                         .AddInMemoryCollection()
                         .SetBasePath(Directory.GetCurrentDirectory())
                         .AddJsonFile("config.json", optional: true, reloadOnChange: false)
                         .Build();
        }

        static void Init()
        {
            if(builder == null)
            {
                builder = new ConfigurationBuilder()
                        .AddInMemoryCollection()
                        .SetBasePath(Directory.GetCurrentDirectory())
                        .AddJsonFile("config.json", optional: true, reloadOnChange: false)
                        .Build();
            }
        }

        public static string GetConnectionString(string connName)
         {
           // Init();
            return builder.GetConnectionString(connName);
         }

        public static string GetCustomSettings(string tblName, string keyName)
        {
           // Init();
            return builder.GetSection(tblName)[keyName];
        }

        public static int GetCustomSettingsInt(string tblName, string keyName)
        {
            return int.Parse(builder.GetSection(tblName)[keyName]);
        }
    }
}
