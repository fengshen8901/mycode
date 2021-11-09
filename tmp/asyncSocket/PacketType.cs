using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace asyncSocket
{
    class PacketType
    {
    }

    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct RegPacketType
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string account;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string passWord;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string tel;
    }

    //[StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct RegPacketTypeRes
    {
        public RegPacketTypeRes(int m = -1)
        {
            res = m;
        }
        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public int res;
    }

    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct LoginPacketType
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string account;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string passWord;
    }

    //[StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct LoginPacketTypeRes
    {
        public LoginPacketTypeRes(int m = -1)
        {
            res = m;
        }
        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public int res;
    }
}
