#include <iostream>
#include <set>
#include "Tool.h"
#include "MyString.h"
#include "STLalgorithm.h"
#include "MyTree.h"
#include "RBTree.h"

using namespace Tool;

int main()
{

	//Red_Black_Tree RBTree;
	//int _arr[] = { 5,18,2,12,9,15,19,17 };
	//for (int i = 0; i < 8; i++)
	//{
	//	RBTree.RBTree_Insert(_arr[i]);  //Test the insertion interface
	//}
	//RBTree.Preorder_Traversal();    //Test the preorder traversal interface
	//RBTree.RBTree_Delete(18);       //Test the deletion interface
	//RBTree.Preorder_Traversal();
	//RBTree.RBTree_Insert(3);
	//RBTree.Preorder_Traversal();
	//RBTree.RBTree_Delete(12);
	//RBTree.Preorder_Traversal();
	//TreeNode * s = RBTree.Find(17);     //Test the search interface
	//cout << endl << "RBTree Node valued 17 has right child valued " << s->right->key << endl;

	//MyTree<int> tree;
	//tree.PosOrder();


	//STLAlgorithm::StringTest();
	STLAlgorithm::VectorTest();
	//STLAlgorithm::AlgorithmTest();
	
	/*char account[1024];
	while (std::cin >> account)
	{
		std::cout << std::hex;
		auto crc32 = getCRC((unsigned char*)account, strlen(account));
		std::cout << "crc32: " << crc32 << std::endl;
		std::cout << std::dec;
		std::cout << "%100: " << crc32 % 100 << std::endl;
	}*/
	////////////////////////////////////////////////////////
	system("pause");
	return 0;
}

