#include "tree.h"
#include <iterator>

//	Печать	дерева
void BSTree::printPref(pnode &t)		//LKR
{
	if (t != 0)
	{
		printPref(t->lt);
		for (int i = 0; i < 3; i++)
			for (auto j : t->set_data[i])
				cout << j;
		cout << endl;
		printPref(t->rt);
	}
}

void output_tree(pnode node, vector<pnode>& vec, int depth)
{
	if (node->lt == nullptr && node->rt == nullptr)
	{
		vec.push_back(node);
		node->depth = depth;
	}
	else
	{
		output_tree(node->lt, vec, depth + 1);
		output_tree(node->rt, vec, depth + 1);
	}
}

void print_tree(pnode node, int pos, int q)
{
	if (node == nullptr)
	{
		for (int i = 0; i < pos; i++)
			cout << "     ";
		cout << "  " << endl;
		return;
	}


	print_tree(node->rt, pos + 1, q);

	for (int i = 0; i < pos; i++)
		cout << "     ";

	if (node->root && ((node->depth - node->root->depth) > 1))
		cout << "        ";
	for (int i = 0; i < q; i++)
	for (auto j : node->set_data[i])
		cout << j;

	print_tree(node->lt, pos + 1, q);
}
