#pragma once


/*
树的基本术语
	节点的度：一个节点含有的子树的个数称为该节点的度；
	树的度：一棵树中，最大的节点的度称为树的度
	节点的层次：从根开始定义起，根为第1层，根的子节点为第2层，以此类推；
	树的高度或深度：树中节点的最大层次；

二叉树的性质;
	第n层最多有 2的(n-1)次方个结点	(某层,双数)
	深度为n的二叉树,最多有 2的n次方再减1个结点  (总数,单数)
	端结点的个数比度为2的结点多1个

满二叉树的性质：(全满的)
	 一颗树深度为h ，最大层数为k，深度与最大层数相同，k=h ;
	叶子数为2h ;
	第k层的结点数是：2k−1 ;
	总结点数是：2k−1 ，且总节点数一定是奇数。

完全二叉树(完全二叉树是效率很高的数据结构)
	深度为k的，有n个结点的二叉树，当且仅当其每一个结点都与深度为k的 满二叉树 中编号从1至n的结点一一对应时，称之为完全二叉树。

二叉查找树  又称为是二叉排序树（Binary Sort Tree）或二叉搜索树。
	二叉排序树或者是一棵空树，或者是具有下列性质的二叉树：
	若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
	若它的右子树不空，则右子树上所有结点的值均大于或等于它的根结点的值；
	它的左、右子树也分别为二叉排序树。

平衡二叉树(AVL)
	任一结点左右子树高度差的绝对值不超过1
	它或者是一棵空树，或者是具有下列性质的二叉树
	它的左子树和右子树都是平衡二叉树，且左子树和右子树的深度之差的绝对值不超过1。（注：平衡二叉树应该是一棵二叉排序树）

红黑树
	特殊的二叉查找树
	红黑树的特性 :
	(1) 每个节点或者是黑色，或者是红色。
	(2) 根节点是黑色。
	(3) 每个叶子节点是黑色。[注意：这里叶子节点，是指为空的叶子节点！]
	(4) 如果一个节点是红色的，则它的子节点必须是黑色的。
	(5) 从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点。(没有一条路径会比其他路径长出俩倍,接近平衡的二叉树)
*/

//树有四种遍历方式，分别是先序、中序、后序、层次遍历

template<typename T>
struct treeNode
{
	T data;
	treeNode<T>* pLeft;
	treeNode<T>* pRight;
};

template<typename T>
class MyTree
{
public:
	MyTree()
	{
		root = Creat(root);
	}
	~MyTree()
	{
		Release(root);
	}
	void PreOrder()
	{
		PreOrder(root);
	}
	void InOrder()
	{
		InOrder(root);
	}
	void PosOrder()
	{
		PosOrder(root);
	}
private:
	treeNode<T>* Creat(treeNode<T>* p)
	{
		T tmp;
		std::cin >> tmp;
		if (tmp == '#')
		{
			p = nullptr;
		}
		else
		{
			p = new treeNode<T>();
			p->data = tmp;
			p->pLeft = Creat(p->pLeft);
			p->pRight = Creat(p->pRight);
		}
		return p;
	}
	void Release(treeNode<T>* p)
	{
		if (!p) return;		
		Release(p->pLeft);
		Release(p->pRight);
		delete p;
		p = nullptr;
	}
	void PreOrder(treeNode<T>* p)//前序遍历
	{
		if (!p) return;

		std::cout << p->data;
		PreOrder(p->pLeft);
		PreOrder(p->pRight);
	}
	void InOrder(treeNode<T>* p)//中序遍历
	{
		if (!p) return;

		InOrder(p->pLeft);
		std::cout << p->data;
		InOrder(p->pRight);
	}
	void PosOrder(treeNode<T>* p)//后序遍历
	{
		if (!p) return;

		PosOrder(p->pLeft);
		PosOrder(p->pRight);
		std::cout << p->data;
	}

	treeNode<T>* root;
};

