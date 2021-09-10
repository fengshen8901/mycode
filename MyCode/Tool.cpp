#include "Tool.h"

/*char account[1024];
while (std::cin >> account)
{
	std::cout << std::hex;
	auto crc32 = getCRC((unsigned char*)account, strlen(account));
	std::cout << "crc32: " << crc32 << std::endl;
	std::cout << std::dec;
	std::cout << "%100: " << crc32 % 100 << std::endl;
}*/

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