#include "fitch.h"
#include <set>

set<char> set_intersection(set<char> set1, set<char> set2)
{
	set<char> res;

	for (set<char>::const_iterator it = set1.begin(); it != set1.end(); ++it)
	{
		auto search = set2.find(*it);
		if (search != set2.end())
			res.insert(*it);
	}
	for (set<char>::const_iterator it = set2.begin(); it != set2.end(); ++it)
	{
		auto search = set1.find(*it);
		if (search != set1.end())
			res.insert(*it);
	}

	return res;
}

set<char> set_union(set<char> set1, set<char> set2)
{
	set<char> res;

	for (set<char>::const_iterator it = set1.begin(); it != set1.end(); ++it)
		res.insert(*it);

	for (set<char>::const_iterator it = set2.begin(); it != set2.end(); ++it)
		res.insert(*it);

	return res;
}


void up_down(pnode node, int k)
{
	if (node != nullptr)
	{
		if (!node->root)
		{
			set<char> temp;
			for (int i = 0; i < 3; i++)
				if (node->set_data[i].size() > 1)
				{
					char n = *next(node->set_data[i].begin(), 1);
					temp.insert(n);
					node->set_data[i].clear();
					node->set_data[i] = temp;
				}
			temp.clear();
		}
		else
		{
			for (int i = 0; i < 3; i++)
				if (set_intersection(node->set_data[i], node->root->set_data[i]).empty())
				{
					set<char> temp;
					if (node->set_data[i].size() > 1)
					{
						char n = *next(node->set_data[i].begin(), 1);
						temp.insert(n);
						node->set_data[i].clear();
						node->set_data[i] = temp;
					}
					temp.clear();
				}
				else
					node->set_data[i] = node->root->set_data[i];
		}

		up_down(node->lt, k);
		up_down(node->rt, k);
	}		
}

void fitch(pnode tr_node, int q, int n, int& c)
{
	int k, c1, c2;
	k = (n + 1) / 2; // Число узлов рассчитывается по формуле

	if (tr_node->number >= n - k) // Если узел является листом
		c = 0;
	else
	{
		fitch(tr_node->lt, q, n, c1);
		fitch(tr_node->rt, q, n, c2);
		c = c1 + c2;

		vector<set<char>> set_lt = tr_node->lt->set_data;
		vector<set<char>> set_rt = tr_node->rt->set_data;


		for (int i = 0; i < q; i++)
		{
			//c += c1 + c2;
			tr_node->set_data[i] = set_intersection(set_lt[i], set_rt[i]);
			if (tr_node->set_data[i].empty())
			{
				tr_node->set_data[i] = set_union(set_lt[i], set_rt[i]);
				c++;
			}
		}
	}
}


