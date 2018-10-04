#include "fitch_st.h"

void up_down_st1(pnode node, int n, int q, int & c)
{
	int k;
	k = (n + 1) / 2; // Число узлов рассчитывается по формуле

	stack<pnode> st;
	pnode elem = node;
	pnode elem_tmp;
	c = 0;

	while (elem != nullptr || !st.empty())
	{
		if (!st.empty())
		{
			elem = st.top();
			st.pop();

			if (elem->number >= n - k || elem->root)
			{
				pnode elem_tmp = elem->root;

				if (elem_tmp->rt != nullptr)
				{
					vector<set<char>> set_lt = elem_tmp->lt->set_data;
					vector<set<char>> set_rt = elem_tmp->rt->set_data;

					for (int i = 0; i < q; i++)
					{
						elem_tmp->set_data[i] = set_intersection(set_lt[i], set_rt[i]);
						if (elem_tmp->set_data[i].empty())
 						{
							elem_tmp->set_data[i] = set_union(set_lt[i], set_rt[i]);
							if (elem_tmp->set_unions[i] );
							else
							{
								elem_tmp->set_unions[i] = 1;
							
								c++;
							}
						}
					}
					elem->root->set_data = elem_tmp->set_data;
				}
			}

			if (elem->rt != nullptr)
				elem = elem->rt;
			else
				elem = nullptr;
		}
				while (elem != nullptr)
				{
					st.push(elem);
					elem = elem->lt;
				}
	}
}

void fill_set_data(vector<set<char>>& data)
{

	set<char> temp;
	for (int i = 0; i < 3; i++)
	{
		if (data[i].size() > 1)
		{
			char n = *next(data[i].begin(), 1);
			temp.insert(n);
			data[i].clear();
			data[i] = temp;
		}
		temp.clear();
	}

}

void up_down_st2(pnode node)
{
	stack<pnode> st;
	st.push(node);

	while (!st.empty())
	{
		pnode node = st.top();
		st.pop();

		if (node)
		{
			if (node->root)
				for (int i = 0; i < node->set_data.size(); i++)
					if (set_intersection(node->set_data[i], node->root->set_data[i]).empty())
						fill_set_data(node->set_data);
					else
						node->set_data[i] = node->root->set_data[i];
			else
				fill_set_data(node->set_data);

			st.push(node->rt);
			st.push(node->lt);
		}
	}
}
