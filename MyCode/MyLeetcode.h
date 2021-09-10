#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<unordered_set>
#include<algorithm>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:	
	vector<int> twoSum(vector<int>& nums, int target)
	{
		map<int, int> a;
		vector<int> res(2, -1);
		for (int i = 0; i < nums.size(); ++i)
		{
			if (a[target - nums[i]] > 0)
			{
				res[0] = a[target - nums[i]];
				res[1] = i;
				break;
			}
			a[nums[i]] = i;
		}
		return res;
	}

	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		ListNode* pHead = nullptr;
		ListNode* pTail = pHead;
		int carry = 0;
		while (l1 || l2)
		{
			int val = carry;
			if (l1)
			{
				val += l1->val;
				l1 = l1->next;
			}
			if (l2)
			{
				val += l2->val;
				l2 = l2->next;
			}
			
			if (!pHead)
			{
				pHead = pTail = new ListNode(val % 10);
			}
			else
			{
				pTail->next = new ListNode(val % 10);
				pTail = pTail->next;
			}
			
			carry = val / 10;
		}
		return pHead;
	}

	int lengthOfLongestSubstring(string s)
	{
		unordered_set<char> a;

		int len = s.length();
		int rk = -1, res = 0;
		for (int i = 0; i < len; ++i)
		{
			if (i > 0)
			{
				a.erase(s[i - 1]);
			}
			while (rk + 1 < len && !a.count(s[rk+1]))
			{
				++rk;
				a.insert(s[rk + 1]);
			}
			res = max(res, rk - i + 1);
		}
		return res;
	}
};




