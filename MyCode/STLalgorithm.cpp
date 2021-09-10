#include <iostream>
#include <algorithm>

#include <string>
#include <vector>

#include "STLalgorithm.h"
#include "Tool.h"

using namespace std;
using namespace Tool;

void STLAlgorithm::StringTest()
{
	//����
		//string s(char*, begin, len)�����ַ���str�д��±�begin��ʼ������Ϊlen�Ĳ�����Ϊ�ַ�����ֵ    string str("12345", 0, 3)  // "123"
		//string s(char*, len)����C_string����cstr��ǰlen���ַ�����Ϊ�ַ���s�ĳ�ֵ								  string str("12345", 3)		// "123"
		//string s(num, char)������num��c�ַ����ַ���																			  string str(3, 'a')				// "aaa"
		//string s(string, begin)�����ַ���str�д��±�str_index��ʼ���ַ���������λ����Ϊ�ַ�����ֵ   string str1(str, 1)			// "aa"
	//��С������
		//str.size() <= > str.length() ���� string::size_type ����(unsigned int)  �ַ�����ʵ�ʳ���(������'\0')
		//str.max_size()������string�������������ַ������ܴ��һ����(9223372036854775807)
		//str.capacity()�����·����ڴ�֮ǰ��string�����ܰ���������ַ���
		//str.reserve(n);  �ֶ��������·����ڴ�,�ı�capacity()�Ĵ�С,����ȵ�ǰС�Ĳ�����,Ҳ��һ����n�Ĵ�С  string str("hello");  str.reserve(20);
		//str.resize(n); / str.resize(n, char);  �ı䴮�ĳ���,��С�ͽض�('\0'��β), ����char	   str.resize(20, 'p');
	//�Ƚ�
		//֧�� >, >=, <, <=, ==, !=
		//��Ա����compare()  ֧�ֶ��������֧��������ֵ�ͳ��ȶ�λ�Ӵ����бȽ�
		//string str1("hello"), str2("heLLhe");
		//MyPrint(str1.compare(str2));				// 1
		//MyPrint(str1.compare(0, 2, str2));		// -1  str1�±�0��ʼ2��Ԫ����str2�����Ƚ�
		//MyPrint(str1.compare(0, 2, str2, 4, 2)); // 0  str1�±�0��ʼ2��Ԫ����str2���±�4��ʼ2��Ԫ��
	//���룺push_back() �� insert()  ����Ϊchar
	//ɾ����erase()
		//iterator erase(iterator p)��ɾ���ַ�����p��ָ���ַ�																s1.erase(s1.begin() + 1);
		//	iterator erase(iterator first, iterator last)��ɾ���ַ����е���������[first, last) �������ַ�		s1.erase(s1.begin() + 1, s1.end() - 2); 
		//	string& erase(size_t pos, size_t len)��ɾ���ַ����д�����λ�� pos ��ʼ�� len ���ַ�				s1.erase(1, 6);
		//	void clear()��ɾ���ַ����������ַ�
	//�滻   s1.swap(s2);
	//�ַ��滻																																										string s1("hello,world!");
		//string& replace(size_t pos, size_t n, const char *s)������ǰ�ַ�����pos������ʼ��n���ַ����滻���ַ���s           s1.replace(6, 5, "girl");		hello,girl!
		//string& replace(size_t pos, size_t n, size_t n1, char c)������ǰ�ַ�����pos������ʼ��n���ַ����滻��n1���ַ�c  s1.replace(s1.size() - 1, 1, 1, '.');	hello,girl.
		//string& replace(iterator i1, iterator i2, const char* s)������ǰ�ַ���[i1, i2)�����е��ַ����滻Ϊ�ַ���s				s1.replace(s1.begin(), s1.begin() + 5, "boy");	boy,girl.
	//tolower() �� toupper() ���� STL�е� transform �㷨
		//tolower() �� toupper() ����Ϊint(char),תСд,��д
		//transform  ��ĳ����Ӧ����ָ����Χ��ÿ��Ԫ��
			//transform(first,last,result,op);//first���������׵�������lastΪ������ĩ��������resultΪ��Ž����������opΪҪ���в�����һԪ��������
			//transform(first1,last1,first2,result,binary_op);//first1�ǵ�һ���������׵��� ����last1Ϊ��һ��������ĩ��������first2Ϊ�ڶ����������׵�������
			//resultΪ��Ž����������binary_opΪҪ���в����Ķ�Ԫ���� ����; ����Ҫ��֤����������Ԫ�ظ�����Ȳ��У�������׳��쳣
			//string s1("hello"), s2("world");
			////transform(s1.begin(), s1.end(), s1.begin(), toupper);
			//transform(s1.begin(), s1.end(), s2.begin(), s2.begin(), STLAlgorithm::compa);
	//�ָ�/��ȡ�ַ���(ȡ�ִ�)
		//string s2 = s1.substr(2, 4);  //ȡs1�±�2��ʼ4���ַ�
		//s2 = s1.substr(2); //ȡs1�±�2��ʼ�� string::npos		
	//�����Ӵ����ַ�(û�ҵ�����string::npos)
		//find(const char* s, size_t pos = 0)/rfind���ڵ�ǰ�ַ�����pos����λ�ÿ�ʼ�������Ӵ�s�������ҵ���λ������
		//find(char c, size_t pos = 0)/rfind���ڵ�ǰ�ַ�����pos����λ�ÿ�ʼ�������ַ�c�������ҵ���λ������
		//find_first_of(const char* s, size_t pos = 0)/find_last_of���ڵ�ǰ�ַ�����pos����λ�ÿ�ʼ�������Ӵ�s���ַ�(�����������ַ�)�������ҵ���λ������
		//find_first_not_of(const char* s, size_t pos = 0)/find_last_not_of���ڵ�ǰ�ַ�����pos����λ�ÿ�ʼ�����ҵ�һ����λ���Ӵ�s���ַ�(�����������ַ�)�������ҵ���λ������
	//����  
		//��������� str.begin()��str.end()
		//��������� str.rbegin()��str.rend()
	//�� STL �㷨���� string ����
		//	sort(s.begin(), s.end());
	//string ������Ϊ������
		//	string src("Avatar 123 5.2 Titanic K");
		//istringstream istrStream(src); //����src��istrStream����ϵ
		//string s1, s2;
		//int n;  double d;  char c;
		//istrStream >> s1 >> n >> d >> s2 >> c; //��src�����ݵ������������ж�ȡ	

	//	string str = "hello " + "world";  //���󣬱�����һ����string���� string("hello ")
	//ƴ������ += append  stringstream  sprintf
	
	//ת������
		// int atoi(const char *nptr);//stoi
		// std::to_string(value);
}

void STLAlgorithm::VectorTest()
{
	//vector����
		// explicit vector(size_type n);		vector<int> vec(10);  10��Ĭ��ֵԪ��
		// vector<int> vec(10, 1);  10��1;
		// vector<int> vec(b);  ����/�ƶ�����
		// vector<int> vec(b.begin(), b.begin()+3); 
		// vector(initializer_list<value_type>il)	vector<int> vec{1,2,3};

	//Capacity ����
		//empty()/max_size()
		//capacity()/reserve()
		//size()/resize()	
		//shrink_to_fit()	//����size����Ķ����ڴ�
	
	//assign
		// vec.assign(b.begin(), b.begin()+3);
		// vec.assign(size_type n, const value_type& val);
		// vec.assign({1,2,3});
	// push_back , pop_back, emplace_back
	// insert, emplace, swap
	// erase, clear		

	//note:
	// δ��ʼ����vector�������ܽ����±����
		// vector<int> vec;
		// vec[0] = 1;
	//clear()���������ͷ��ڴ�(����Ϊ�Ż�Ч����������)��
		//	clearʵ����������Ϊvector������������ж��������������(����еĻ�), Ȼ���ʼ��size��Щ�������þ��ð����еĶ�������ˡ�
		//	�����ͷ��ڴ�����vector��������������еģ�����һ������vector���������纯������)��
		//	����������������ж���ᱻ������Ȼ������allocator�е�deallocate�������ն�������ڴ档
		// ���� vector<int>(vec).swap(vec); ���� vec.shrink_to_fit();
	vector<int> vec(3);
	MyPrint(vec.capacity());

}

void STLAlgorithm::AlgorithmTest()
{
	//����
	/*
		auto it = find(vec.begin(), vec.end(), 2);
		auto it = find_if(vec.begin(), vec.end(), [](int val) { return val % 2 == 0; });

		it = find_first_of(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
		//����vec1,��vec2������ȵ�,�ҵ�����, ����vec1������,û�о�end()

		it = find_end(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
		//��vec1������vec2�Ӵ���ȫƥ������һ��,�ҵ�����, ����vec1������,û�о�end()

		auto it = search(vec.begin(), vec.end(), vec1.begin(), vec1.end());
		auto it = search_n(vec.begin(), vec.end(), 2, 8); //�����ŵ�2��8

		auto it = count(vec.begin(), vec.end(), 8); //ͳ���м���8
		auto it = count_if(vec.begin(), vec.end(), [](int val) { return val % 2 == 0; });

		���ֲ���(��������)
		auto it = lower_bound(vec.begin(), vec.end(), 4);     // ��һ�����ڵ���
		auto it = upper_bound(vec.begin(), vec.end(), 4);    // ��һ������
		���ֲ���(��������)
		auto it = equal_range(vec.begin(), vec.end(), 8);
		cout << *(it.first )<< ", index: " << it.first - vec.begin() << endl;
		cout << *(it.second )<< ", index: " << it.second - vec.begin() << endl;
		���ֲ���(��������)
		bool isHave = binary_search(vec.begin(), vec.end(), 8);

		bool isequal = equal(vec1.begin(), vec1.end(), vec2.begin());  vec2�ĳ��ȱ���>=vec1
		bool isequal = equal(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

	*/

	//����
	/*
		sort(vec.begin(), vec.end(), greater<>());  Ĭ��less<>()
		stable_sort  ͬ��,�����Ԫ�ر������λ�ò���

		partial_sort(vec.begin(), vec.begin() + 4, vec.end());	ֻ����ǰ��������,��������(partial  adj. �ֲ���),Ĭ�ϴ�С����
		partial_sort(vec.begin(), vec.begin() + 4, vec.end(), greater<>());

		�ϲ�(��������)vec,vec1��vec2��, vec2���������
		vector<int> vec2(15);
		merge(vec.begin(), vec.end(), vec1.begin(), vec1.end(), vec2.begin());
	*/

	/*
		�������
		random_shuffle(vec2.begin(), vec2.end());
		��ת
		reverse(vec2.begin(), vec2.end());
		��ת, ��[0,1)��[1,2)���� 1�ͳ���begin
		rotate(vec2.begin(), vec2.begin()+5, vec2.end());

		��С,���Ԫ��
		auto it = min_element(vec2.begin(), vec2.end());  // auto it = min(vec2.begin(), vec2.end());
		auto it = max_element(vec2.begin(), vec2.end()); // max()

		��������
		generate(vec2.begin(), vec2.end(), []() { return rand() % 5; });

		��vec1���Ƶ�vec2, vec2�����㹻��
		copy(vec1.begin(), vec1.end(), vec2.begin());
		��vec1��Ԫ�ؾ��������ٸ��Ƶ�vec2, vec2�����㹻��
		transform(vec1.begin(), vec1.end(), vec.begin(), [](int v) {  return v + 100; });
		transform(vec.begin(), vec.end(), vec.begin(), [](int v) {  return v + 100; });  //��������Ԫ�ص��ô�����

		�滻 8����-8
		replace(vec.begin(), vec.end(), 8, -8);
		replace_if

		�޳�(����������ɾ��) remove��������ɾ��,ֻ��Ų������,����size��û��
		remove(vec.begin(), vec.end(), 8);
		remove_if
		//auto itr = std::remove(vec.begin(), vec.end(), 6);
		//if (itr != vec.end())
		//vec.erase(itr, vec.end()); ����ɾ��
		//auto itr = vec.begin();
		//auto lastItr = itr;
		//while (itr != vec.end())
		//{
		//	if (*itr != 6)
		//	{
		//		*lastItr = *itr;
		//		++lastItr;
		//	}
		//	++itr;
		//}
		//}

		���ڵ�ȥ��(����������ɾ��)
		unique(vec.begin(), vec.end());

		���, ȫд��8
		fill(vec.begin(), vec.end(), 8);
		fill_n(vec.begin() , 3, 99);  ǰ3���ĳ�99( vec��3��,����Խ��)

		
	*/
}
