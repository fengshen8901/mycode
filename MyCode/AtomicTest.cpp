#include "AtomicTest.h"
#include <iostream>

//��׼ԭ�����ͣ�������������һ��is_lock_free()��Ա��������atomic_flag��,����Ƿ�������
//ֱ����ԭ��ָ�����(true), ���������(false)
// 
//std::atomic_flag,һ���ǳ��򵥵Ĳ�����ʶ�������ģ���������֤������
// Ψһ��֤������Ψһ��Ҫ�����ʼ��
//��򵥵ı�׼ԭ������() std::atomic_flag f = ATOMIC_FLAG_INIT; ����������ʼ�������״̬��
//ֻ�� ����(����), ���clear()�����ò���ѯ��ǰ��ֵ(test_and_set())

//��׼ԭ�������ǲ��ɸ��Ʋ��ɸ�ֵ�ģ�û�п�������Ϳ�����ֵ�����
// load(),��
//  store(), д
// exchange(), ��-�޸�-д
// ָ��ԭ������֧���Լӡ��Լ���+=��-=�������
// fetch_add(), fetch_sub()   ��������ӣ���-�޸�-д����
// ����ԭֵ�������������  a.fetch_add(2); ����a֮ǰ��ֵ��a����ƫ��2
// 
// �Ƚ�/����
// �Ƚ�ԭ�ӱ���ֵ��Ԥ��ֵ�������洢����ֵ����true, ������Ԥ��ֵ����Ϊԭ�ӱ���ʵ��ֵ����false
// (Ԥ��ֵ���ã�����ֵ��
// compare_exchange_weak(), ����αʧ��(�Ƚ�ֵ��ȣ�������ԭ�����δ����)��ͨ������ѭ����
// while(!b.compare_exchange_weak(expected, desired) && ! expected)
// compare_exchange_strong()
// 
//��׼ԭ�ӵ����Ͳ���֧�� ǰ׺/��׺���Լ�/�Լ�, +=,-=,&=,|=,^=, fetch_add, fetch_sub,
//fetch_and, fetch_or, fetch_xor
// ֻ�г˷���������λ���������ȱʧ��
// ����ֵ(double, float)û��ԭ�ӵ���������

//std::atomic<>������ģ�壬�����Զ������͵�ԭ�ӱ���
// ���Զ������ͱ�������һ����׼��
//     ��һ��ƽ��(trivial)�Ŀ�����ֵ�����, ��ζ�Ÿ����Ͳ���ӵ���κ��麯��������࣬
// ���ұ���ʹ�ñ��������ɵĿ�����ֵ�������
//     ���л���ͷǾ�̬���ݳ�ԱҲ��������һ��ƽ���Ŀ�����ֵ������������������
// ��memcpy��һ���ȼ۵Ĳ������ڸ�ֵ����
//     �����ǰ�λ��ȿɱȽϣ��������ܹ�ʹ��memcmp�Ƚ�ʵ���Ƿ����
// ����Զ�����Ĵ�С��һ��int��void*��С��ͬ���󲿷�ƽ̨�ܹ�ʹ��ԭ��ָ��
//
//ԭ�Ӳ��������ɺ������ǳ�Ա����-ȫ�ֺ�����
// ��������Ӧ�ĳ�Ա�����������ģ�ֻ�Ǵ���һ��atomic_ǰ׺��ָ���ڴ�˳��Ļ���_explicit��׺
// �磺 std::atomic_load(&a); std::atomic_load_explicit(&a, std::memory_order_seq_cst)
// ���ṩ����ԭ����Ϊ����std::shared_ptr<>ʵ�������ɺ��������Ե�ԭ�Ӳ����У�
//  ����(load)���洢(store)������(exchange) �ͱȽ�/����(compare/exchange)
// ����std::shared_ptr<>*��Ϊ��һ������
//
//��ԭ�������ϵ�ÿһ������������һ����ѡ���ڴ�˳���������������ָ��������ڴ�˳������
// ���в�����Ĭ��˳��Ϊstd::memory_order_seq_cst
	//�洢��store): 
		//std::memory_order_relaxed(��ɢ);  std::memory_order_release;  std::memory_order_seq_cst
	//���루load):
		//std::memory_order_relaxed; std::memory_order_consume; std::memory_order_acquire; 
		//std::memory_order_seq_cst
	//��-�޸�-д��read-modify-write):
		//std::memory_order_relaxed; std::memory_order_consume; std::memory_order_acquire
		//std::memory_order_release;  std::memory_order_acq_rel; std::memory_order_seq_cst 
//
// ������˳��ѡ����ʵ����������ģ��
// ˳��һ��(sequentially consistent) memory_order_seq_cst
// ���-�ͷ�(acquire-release) ... ... ���� memory_order_consume �Ƚ��ر��������� 
// ��ɢ(relaxed) memory_order_relaxed
//

//std::this_thread::yield
void AtomicTest::Test()
{
	std::atomic_int a = 1; 
	int tmp = 1;
	std::cout << a.is_lock_free() << std::endl;
	if (a.compare_exchange_strong(tmp, 0))
	{
		std::cout << "true" << a << ", " << tmp << std::endl;
	}
	else
	{
		std::cout << "false" << a << ", " << tmp << std::endl;
	}
	//std::is_trivial<int>::value
}
