#pragma once
#include <assert.h>
//MyStrlen
//MyStrcpy
//MyStrcmp
//MyStrcat
//class MyString


//必须是以'\0'结尾; 结果不包括'\0'
int MyStrlen(const char* src);

char* MyStrcpy(char* dst, const char* src);

int MyStrcmp(const char* a, const char* b);

bool MyStrcat(char* dest, const char* src);

class MyString
{
public:
	MyString(const char* src = nullptr);
	MyString(const MyString& src);
	MyString(MyString&& src) noexcept;
	~MyString();

	MyString& operator=(const MyString& src);
	MyString& operator=(MyString&& src) noexcept;
	
	MyString operator+(const MyString& src);
	MyString& operator+=(const MyString& src);

	bool operator==(const MyString& src) const;
	char& operator[](int n);

	const char* c_str() const
	{ 
		return pData;
	}
	int length() const
	{
		return len;
	}
private:
	char* pData;
	int len;
};