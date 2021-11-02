#pragma once

//C++��׼�涨������һ��������(�Ǹ���)���󶼱�����з����С
//����Ĵ�СΪ1����Ϊ�������ʵ������ʵ������Ȼ���ڴ���ռ��һ��λ��
// ָ����32λ��ռ4���ֽ�,64λ��ռ8

//////////////////////////////////////////////////////////////////////////////////////////
class abase1
{
private:
	char a;
	int b;
	double c;
};
//  1    4
//  8
//  16
class abase2
{
private:
	char a;
	double b;
	int c;
};
//  1    
//  8
//  4
//  24

//////////////////////////////////////////////////////////////////////////////////////////
class bBase
{
private:
	char a;
public:
	virtual void f();
	virtual void g();
};
// vfptr
// 1
// 16

class bDerived :public bBase
{
private:
	double b;
public:
	void g();
	virtual void h();
};
// vfptr - self
// 1
// 8
// 24

class bDerived1 :public bBase
{
private:
	int b;
public:
	void f();
};
// vfptr
// 1  
// 4
//24

class bDerived2 :public bDerived1
{
private:
	double b;
public:
	void g();
	virtual void h();
};
// vfptr - self
// 1 
// 4
// 8
// 32
//////////////////////////////////////////////////////////////////////////////////////////
class cBase1
{
private:
	char a;
public:
	virtual void f();
	virtual void g1();
};
// vfptr
// 1
// 16
class cBase2
{
private:
	int b;
public:
	virtual void f();
	virtual void g2();
};
// vfptr
// 4
// 16
class cBase3
{
private:
	double c;
public:
	virtual void f();
	virtual void g3();
};
// vfptr
// 8
// 16
class cDerived :public cBase1, public cBase2, public cBase3
{
private:
	double d;
public:
	void f();
	virtual void derived_func();
};
// vfptr1 - self
// 1
// vfptr2
// 4
// vfptr3
// 8
// 8
// 56
//////////////////////////////////////////////////////////////////////////////////////////
//��̳� ���μ̳�
class dBase
{
public:
	virtual void f();
private:
	int a;
};
// vfptr
// 4
// 16
class dBase1 :virtual public dBase
{
public:
	virtual void f();
	//virtual void g();
private:
};
//vfself--vfbase
//0
//(vfbase) 0
//vfbase
//vb
//4
//24

// -- vfptr --�Լ���,������µ��麯��
// vbptr
// 0--�Լ��ĳ�Ա���� 
// vfptr base
// 4
// 24 / 32
class dBase2 :virtual public dBase
{
public:

};
// vbptr
// 0--�Լ��ĳ�Ա���� 
// vfptr base
// 4
// 24
class dDerived :public dBase1, public dBase2
{
public:
	virtual ~dDerived();
	virtual void h();
	virtual void f();
private:
	double b;
};
// dBase1 vfptr - self vfptr
// vbptr
// 0--dBase1��Ա���� 
// 0--dBase2 vfptr
// vbptr
// 0--dBase2��Ա���� 
// 8
// dBase vbptr
// 4
// 48


class ClassSize
{
public:
	static void Test();

	void get();
	void get() const;
};

