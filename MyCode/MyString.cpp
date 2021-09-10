#include "MyString.h"

int MyStrlen(const char* src)
{
	if (!src) return 0;
	int len = 0;
	while (*src++ != '\0')
	{
		++len;
	}
	return len;
}

char* MyStrcpy(char* dst, const char* src)
{
	assert(dst && src);

	auto res = dst;
	while ( (*dst++ = *src++) != '\0');
	return res;
}

int MyStrcmp(const char* a, const char* b)
{
	assert(a && b);
	while (true)
	{
		if (*a == *b && *a == '\0') return 0;

		if (*b == '\0') return 1;
		if (*a == '\0') return -1;

		if (*a > *b) return 1;
		if (*a < *b) return -1;
		++a;
		++b;
	}
	return 0;
}

bool MyStrcat(char* dest, const char* src)
{
	assert(dest && src);
	char* tmp = dest;
	while (*dest != '\0')
	{
		++dest;
	}

	while ((*dest++ = *src++) != '\0');
	return tmp;
}

MyString::MyString(const char* src)
{
	if (!src)
	{
		len = 0;
		pData = new char[1];
		*pData = '\0';
	}
	else
	{
		len = MyStrlen(src);
		pData = new char[len + 1];
		MyStrcpy(pData, src);
	}
}

MyString::MyString(const MyString& src):MyString(src.pData)
{

}

MyString::MyString(MyString&& src) noexcept
{
	len = src.len;
	pData = src.pData;

	src.len = 0;
	src.pData = nullptr;
}

MyString::~MyString()
{
	delete[] pData;
	len = 0;
}

MyString& MyString::operator=(MyString&& src) noexcept
{
	len = src.len;
	pData = src.pData;

	src.len = 0;
	src.pData = nullptr;
	return *this;
}

MyString& MyString::operator=(const MyString& src)
{
	len = src.len;
	pData = new char[len + 1];
	MyStrcpy(pData, src.pData);
	return *this;
}

bool MyString::operator==(const MyString& src) const
{
	if (len != src.len) return false;
	return MyStrcmp(pData, src.pData) == 0;
}

char& MyString::operator[](int n)
{
	if (n < 0 || len <= n) return pData[len - 1];
	return pData[n];
}

MyString MyString::operator+(const MyString& src)
{
	MyString newStr;
	newStr.len = len + src.len;
	newStr.pData = new char[newStr.len + 1];
	MyStrcpy(newStr.pData, pData);
	MyStrcat(newStr.pData, src.pData);
	return newStr;
}

MyString& MyString::operator+=(const MyString& src)
{
	len += src.len;
	char* tmp = new char[len + 1];	//防止自己加自己
	MyStrcpy(tmp, pData);
	MyStrcat(tmp, src.pData);
	delete[] pData;
	pData = tmp;
	return *this;
}
