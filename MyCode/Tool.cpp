#include "Tool.h"

namespace Tool
{
	UINT32 getCRC(unsigned char* buf, int nLength)
	{
		if (nLength < 1)
			return 0xffffffff;

		UINT32 crc = 0;
		crc = crc ^ 0xffffffff;

		for (int i(0); i != nLength; ++i)
		{
			crc = table[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
		}

		crc = crc ^ 0xffffffff;

		return crc;
	}
}