#pragma once


class StlTest
{

public:
	//�����㷨
	static void FindTest();

	//�����ͨ���㷨
	static void SortAndCommon();

	//ɾ�����滻�㷨
	static void RemoveAndReplace();

	//��������㷨
	static void PermutationTest();

	//�����㷨
	static void MathTest();

	//���ɺ�����㷨
	static void TransformTest();

	//��ϵ�㷨
	static void EqualTest();

	//�����㷨
	static void SetTest();

	//���㷨
	static void HeapTest();
};

//�º�����Functor��
//STL�ڽ��ķº������������<functional>ͷ�ļ�
//1��������º���
//�ӣ�plus<T>
//����minus<T>
//�ˣ�multiplies<T>
//����divides<T>
//ģȡ��modulus<T>
//�񶨣�negate < T>
//2����ϵ������º���
//���ڣ�equal_to<T>
//�����ڣ�not_equal_to<T>
//���ڣ�greater<T>
//���ڵ��ڣ�greater_equal<T>
//С�ڣ�less<T>
//С�ڵ��ڣ�less_equal<T>
//�߼��룺logical_and<T>
//�߼���logical_or<T>
//�߼���logical_no<T>

//��������Adaptor��
//��׼���ṩ������˳��������������queue(FIFO����)��priority_queue(���ȼ�����)��stack(ջ)
//stack<int, vector<int> >ʵ����ջ�Ĺ��ܣ������ڲ�ʹ��˳������vector<int>���洢����
//����		Ĭ��˳������	����˳������				˵��
//stack	deque		vector��list��deque
//queue	deque		list��deque				�������������ṩpush_front()����
//priority_queue		vector	vector��deque	�������������ṩ������ʹ���

