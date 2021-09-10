#pragma once

/**RBTree.h
 * The Binary Search Tree Data Structure in C++
 * Time Cost : Inorder / Preorder / Postorder Traversal : O(n)
 *             Search / Find / Insert / Delete / Minimum / Maximum : O(h)
 *             Transplant / Rotation : O(1)
 * Thanks to Introduction to Algorithms (CLRS) Chapter 13
 * Thanks to Stanford MOOC of "Algorithms : Part I"
 * Author: Zheng Chen / Arclabs001
 * Email : chenzheng17@yahoo.com
 * Copyright 2015 Xi'an University of Posts & Telecommunications. All rights reserved.
 */
#include <iostream>
#include <stack>
#include <cstdlib>
#define INF 0x7FFFFFFF
using namespace std;

enum COLOR { RED, BLACK };

struct TreeNode {
	int key;
	TreeNode *parent;
	TreeNode *left, *right;
	COLOR color;

	TreeNode& operator = (TreeNode& node)  //Reload the "=" for assignment
	{
		this->key = node.key;
		this->parent = node.parent;
		this->left = node.left;
		this->right = node.right;
		this->color = node.color;
		return *this;
	}
};

static TreeNode NULL_NODE = { INF,nullptr,nullptr,nullptr,BLACK };

class Red_Black_Tree
{
private:
	TreeNode * root;
	int _size;
	TreeNode * NIL;

	void Left_Rotate(TreeNode *x);
	void Right_Rotate(TreeNode *x);

	//Insertion or deletion may cause red-black tree's quality destroyed
	//So we just try to fix it by this two options. 
	void RB_Insert_FixUp(TreeNode *z);
	void RB_Delete_FixUp(TreeNode *z);

	void Transplant(TreeNode * u, TreeNode * v);

	TreeNode * Tree_Minimum(TreeNode * root);
	TreeNode * Tree_Maximum(TreeNode * root);

public:
	Red_Black_Tree() { _size = 0; NIL = &NULL_NODE; root = &NULL_NODE; }

	void RBTree_Insert(int _key);
	bool RBTree_Delete(int _key);

	void Preorder_Traversal();
	TreeNode * Find(int _key);
};
