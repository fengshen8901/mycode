#include <iostream>
#include <algorithm>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "STLalgorithm.h"
#include "Tool.h"

using namespace std;
using namespace Tool;


//
// 3������������
// ÿ���������������������죬Ĭ�Ϲ��촴��һ���ն��� ����һ�������Ĺ��캯��
// Ĭ������£�stack, queue�ǻ���dequeʵ�֣�priority_queue����vector֮��ʵ�ֵ�
// �������ڴ�����������ָ��
// 
// stack<string, vector<string> > str_stk;  vectorʵ�ֵ�ջ
// stack<int> stk;
// stk.push(1);
// auto val = stk.top();
// stk.pop();
// 
// priority_queue ���ȶ���  push ����Ԫ�ص���β (������)
// ������У�С����
// priority_queue <int, vector<int>, greater<int> > q;
// ������У��󶥶� (Ĭ��)
// priority_queue <int, vector<int>, less<int> >q;

//���������
// back_inserter
// front_inserter
// inserter
//   auto it = inserter(vec, iter); �õ�һ�����������
//   *it = val;  <=>  it = vec.insert(iter, val);  ++it;
// 
// vector<int> vec{1,2,3};
// auto it = back_inserter(vec);
// *it = 4;
//  *it = 5;
// auto iter = inserter(vec, vec.end());
// *iter = 6;
//

// 
// ˳����������
// vector, deque, list, forward_list, array, string
//
// list��forward_list��Ա����
// lst.merge(lst2);
// lst.merge(lst2, comp);
//   lst,lst2������������ģ��ϲ���lst2��Ϊ��
// lst.remove(val);
// lst.remove_if(pred); 
//   ����eraseɾ������������ÿ��Ԫ�أ�ͨ�ð汾����ɾ����
// lst.reverse();  ��תԪ��˳��
// lst.sort();
// lst.sort(comp);
// lst.unique();
// lst.unique(pred);
//   ����eraseɾ�������ظ�Ԫ��
// 
// splice/splice_after  ���; �ʽ�(��������);
// lst.splice(p, lst2);	 ��lst2������Ԫ���ƶ���lst��p֮ǰ�����������������ͬ���Ҳ�����ͬһ����
// lst.splice(p, lst2, p2);  ��lst2��p2ָ���Ԫ���ƶ���lst��p֮ǰ������ͬһ����
// lst,splice(p, lst2, b, e);  ��lst2�и����ķ�ΧԪ���ƶ���lst��p֮ǰ������ͬһ������p����ָ�������Χ��Ԫ��
// 
//˳�����������������ƣ���vectorΪ��
void STLAlgorithm::VectorTest()
{
	//����
		// vector<int> vec(10);  10��Ĭ��ֵԪ��
		// vector<int> vec(10, 1);  10��1;
		// vector<int> vec1(vec);  ����/�ƶ�����   ���ͱ���ƥ��
		//		�����������Ͳ������������ֵ����array���ԣ���ʾ��ֵ������{}����Ϊ���ܻ��С��ͬ��
		// vector<int> vec(b.begin(), b.begin()+3);  ���Ϳ��Բ�ͬ��Ԫ�ؼ����ת��
		//	    vector<string> vst;  
		//     vector<const char*> vc(vst.begin(), vst.end());
		// vector(initializer_list<value_type>il)	vector<int> vec{1,2,3};

	//Capacity ����
		//empty()/max_size()
		//capacity()/reserve()
		//size()/resize()	  //forward_list��֧�� size()
		//shrink_to_fit()	//����size����Ķ����ڴ�

	//assign
		// vec.assign(b.begin(), b.begin()+3);
		// vec.assign(size_type n, const value_type& val);
		// vec.assign({1,2,3});	

	// swap(v1, v2);  Ԫ�ر���δ������ֻ�����������������ڲ����ݽṹ
	// ���е�����������ʧЧ����ָ�򽻻�֮ǰ��������string��������ʧЧ��
	// array�������������ǵ�Ԫ�أ�������ָ���Ԫ���Ѿ������ı�
	// 
	// ��ϵ����� ���Ƚ�������С��������ͬ���͵�������Ԫ��������ͬ
	// ������string�ıȽϣ���Ҫȡ���ڵ�һ�������Ԫ�صĴ�С
	// 
	// ˳���������Ԫ��
	// 	c.push_back(t); c.emplace_back(args);
	// 	c.push_front(); c.emplace_front(args);
	// 	c.insert(p, t); c.emplace(p, args);
	// 	c.insert(p, n, t);  c.insert(p, b, e);  c.insert(p, il);  //il -> initializer_list
	// forward_list��֧��push_back,emplace_back;���Լ�רҵ�汾��insert,emplace
	// vector,string��֧��push_front,emplace_front;
	// 
	// ɾ��Ԫ��
	//     c.pop_back();  c.pop_front();
	// 	c.erase(p);  c.erase(b, e);
	// 	c.clear();    <=>  c.erase(c.begin(), c.end() );
	// forward_list��֧��pop_back,���Լ�����汾��erase
	// vector,string��֧��pop_front
	// 
	// �����forward_list����
	//   ��ɾ����3��Ԫ��ʱ����2��ָ���4�����ҵ�3����ǰһ��(��2��)�����ң�
	//  �����ṩ����Ĳ��� ���/ɾ����ǰ����һ��Ԫ��
	// 	   lst.before_begin();  lst.cbefore_begin();    ��ǰ(��Ԫ��֮ǰ�������ڵ�Ԫ��)
	// 	   lst.insert_after(p, t);  lst.insert_after(p, n, t);
	// 	   lst.insert_after(p, b, e);  lst.insert_after(p, il);
	// 	   lst.emplace_after(p, args);
	// 	   lst.erase_after(p);  lst.erase(p, b, e);
	// 
	
	
	//note:
	// δ��ʼ����vector�������ܽ����±����
		// vector<int> vec;
		// vec[0] = 1;
	//clear()���������ͷ��ڴ�(����Ϊ�Ż�Ч����������)��
		//	clearʵ����������Ϊvector������������ж��������������(����еĻ�), Ȼ���ʼ��size��Щ�������þ��ð����еĶ�������ˡ�
		//	�����ͷ��ڴ�����vector��������������еģ�����һ������vector���������纯������)��
		//	����������������ж���ᱻ������Ȼ������allocator�е�deallocate�������ն�������ڴ档
		// ���� vector<int>(vec).swap(vec); ���� vec.shrink_to_fit();
	//�����һ��ѭ���в���/ɾ�������е�Ԫ�أ���Ҫ����end()���صĵ���������ʧЧ��Ӧ��ÿ�ε���while(itr != c.end())


}

// 
// ������������(8�֣�
// map, set
// multimap, multiset
// unordered_map, unordered_set
// unordered_multemap, unordered_multeset
// ���������ļ�ֵ���ͱ��붨��Ԫ�صıȽϷ�������<������ָ������ıȽϺ���ָ��
//
// �������
// c.insert(v);
// c.emplace(args);
// c.insert(b, e);
// c.emplace(il);
//   c.insert(p, v); c.emplace(p, args);  pΪ��ʾ���Ŀ�ʼ������Ԫ��Ӧ�ô洢��λ��
// ����ֵ��������(unordered)�ظ��ؼ��ֵ�����������pair, 
//	    first ��ӵ���Ԫ�صĵ�����
//     second (bool),�Ѿ�����ɶҲ���ɷ���false,����ɹ�����true
//  ����(unordered)�ظ��ؼ��ֵ�������������Ԫ�صĵ�����
//
// ɾ������
// c.erase(key); ����ɾ����Ԫ������
// c.erase(p); ����ɾ������һ��������
// c.erase(b, e); ����e
// 
// �±����
// setû���±��������Ϊû�С�ֵ����
// ���ܶ�multimap, unordered_multimap�����±����
// ��map�����±����ʱ����������ڻᴴ��һ��Ԫ�ز����뵽map�У�����ֵ������ֵ��ʼ��(0)
// 
// c.find(k); ����һ��������
// c.count(k); ���عؼ��ֵ���k��Ԫ������
// c.lower_bound(k);  ���ص�һ���ؼ��ֲ�С��k��Ԫ�صĵ�����
// c.upper_bound(k);  ���ص�һ���ؼ��ִ���k��Ԫ�صĵ�����
// c.equal_range(k);  ����һ��pair, �ؼ��ֵ���k��Ԫ�صķ�Χ [ )����û�У�����c.end()
//
// Ͱ
//   ��������������Ԫ�ؼ��Ĺ�ϣֵ�浽��Ӧ��Ͱ����ͬ�Ĺ�ϣֵԪ�ش浽��ͬ��Ͱ
// Ͱ�ӿ�
// c.bucket_count();  ����ʹ�õ�Ͱ����Ŀ
// c.max_bucket_count();  ���������ɵ�����Ͱ������
// c.bucket_size(n);  ��n��Ͱ��Ԫ�ظ���
// c.bucket(k);  �ؼ���k��Ԫ���ڵڼ���Ͱ
// Ͱ����
// local_iterator/const_local_iterator  Ͱ��Ԫ�صĵ���������
// c.begin(n); c.end(n);  Ͱn����(β��)Ԫ�ص�����
// c.cbegin(n); c.cend(n);
// ��ϣ����
// c.load_factor()  ÿ��Ͱ��ƽ��Ԫ������(float)
// c.max_load_factor();  
// c.rehash(n);  ����洢��ʹ��bucket_count>=n
// c.reserve(n);  ����洢��ʹ��c���Ա���n��Ԫ���Ҳ���rehash
// 
//���������Թؼ������͵�Ҫ��
// ��==��������͹�ϣ���㺯�� ����
//

size_t myhash(const Element& v)
{
	return hash<string>()(v.str);
}

bool CompE(const Element& a, const Element& b)
{
	return a.str == b.str;
}

void STLAlgorithm::MapTest()
{
	//Ͱ��������С����ϣ����ָ�룬������ж������ָ��
	unordered_map<Element, int, decltype(myhash)*, decltype(CompE )*> m(42, myhash, CompE);
	m["abc"] = 2;
	m["bcd"] = 3;
	cout << m.begin()->second << endl;;
	unordered_set<Element, decltype(myhash)*, decltype(CompE)*> s(2, myhash, CompE);
	s.insert("abc");
	

	cout << s.bucket_count();
}

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
		copy_if(beg, end, dest, unaryPred);
		copy_n(beg, n, dest);

		move(beg, end, dest);

		��vec1��Ԫ�ؾ��������ٸ��Ƶ�vec2, vec2�����㹻��
		transform(vec1.begin(), vec1.end(), vec.begin(), [](int v) {  return v + 100; });
		transform(vec.begin(), vec.end(), vec.begin(), [](int v) {  return v + 100; });  //��������Ԫ�ص��ô�����
		
		transform(beg, end, beg2, dest, binaryOp);  �������ж�Ԫ����

		�滻 8����-8
		replace(vec.begin(), vec.end(), 8, -8);
		replace_if

		���, ȫд��8
		fill(vec.begin(), vec.end(), 8);
		fill_n(vec.begin() , 3, 99);  ǰ3���ĳ�99( vec��3��,����Խ��)

		���Ų���
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
		unique(beg, end, binaryPred);

		Χ��midָ���Ԫ�ؽ���Ԫ��ת����Ԫ��mid��Ϊ��Ԫ�أ������mid+1��end, beg��(mid-1),����ԭ��begin������
		

		
	*/
}
