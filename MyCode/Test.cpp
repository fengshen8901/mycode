

//Big - Endian（大端）：高位字节排放在内存的低地址端，低位字节排放在内存的高地址端。
//Little - Endian（小端）：低位字节排放在内存的低地址端，高位字节排放在内存的高地址端。

//const char* p = "abc";  //指向常量的指针  底层const
//char a = 'a';
//char *const p1 = &a;	//常量指针  顶层const
// constexpr int n = 1;

//内置类型的变量未显示初始化，定义在函数体外的将被默认初始化，
//在函数体内不被初始化，变量未定义，访问将引发错误

//C++中IO操作都可以用流对象来实现，一般有三种流对象：
//1）控制台流对象: istream, ostream, iostream
//2）文件流对象 : fstream, ifstream, ofstream
//3）字符串流对象 : stringstream, istringstream, ostringstream