#include "io.h"
#include "fitch.h"
#include "fitch_st.h"
#include "tree.h"
#include <fstream>
#include <ctime>  

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cerr << "Input file not specialized" << endl;
		return -1;
	}

	//Ќа вход подаютс€ следующие данные из файла: число символов в последовательност€х, число листьев дерева, последовательности листьев,
	//ребра дерева в виде пар вершин (e.g. 0 4), где первое число - предок, второе - потомок.

	int t = clock();

	BSTree res = build_trees(string(argv[1]));

	vector<pnode> leaves;

	//«аполнение вектора узлами-листь€ми
	output_tree(res.root, leaves);

	int q = res.root->set_data.size(); 
	int n = 2 * leaves.size() - 1;
	int c = 0; int z = 0;

	//¬ывод листье дерева
	cout << "Tree leaves: " << endl;
	print_tree(res.root, z, q);
	cout << endl;


	cout << "Algorithm Fitch recursive or with stack? (R/S) " << endl;

	char p;
	cin >> p;

	if (p == 'R')
	{
		fitch(res.root, q, n, c);
		up_down(res.root, 2 * leaves.size() - 1);
	}
	else
		if (p == 'S')
		{
			up_down_st1(res.root, n, q, c);
			up_down_st2(res.root);
		}
		else
			cout << "Wrong input." << endl;


	//res.printPref();
	int x; x = 0;
	ofstream out(string(argv[2]), ofstream::out);
	print_tree(res.root, x, q);
	x = 0;
	print_tree_file(out, res.root, x, q);

	cout << "Cost of tree - " << c << endl;

	cout << "It took "
		<< t << " tics or  "
		<< ((float)t) / CLOCKS_PER_SEC << " seconds of time for computing." << endl;

	system("pause");

	return 0;
}