#include "io.h"
#include <fstream>
#include <algorithm>
#include <set>


//Процедура ввода дерева из файла. На вход подается имя файла, число символов в последовательностях, число листьев дерева, 
//последоватнльости листьев и ребра 
void read_from_file(string filename, int& q, int& k, vector<char*>& sequences, vector<vector<int>>& edges)
{
	ifstream f(filename);

	f >> q; //Считываем число символов в последовательностях

	int n;
	f >> n; //Считываем число листьев
	k = 2*n-1; //Число узлов рассчитывается по формуле

	char* buf = new char[4];
	sequences = vector<char*>(n);

	for (int i = 0; i < n; i++)
	{
		f >> buf; //Считываем символы последовательностей каждого узла дерева
		sequences[i] = new char[q];

		for (int j = 0; j < q; j++)
		{
			sequences[i][j] = buf[j];
		}

	}

	edges = vector<vector<int>>(k - 1); //Ребра дерева, считываемые из файла
	for (int i = 0; i < k - 1; i++) // k 
	{
		edges[i] = vector<int>(2);
		f >> edges[i][0] >> edges[i][1]; // Сначала считывается предок, затем потомок
	}

	f.close();

	sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {return a[0] < b[0]; }); //Вектор ребер сортируется по старшинству
	//(сначала ребра из корня, затем по возрастанию номера вершины)
}

BSTree build_tree(int q, int k, vector<char*>& sequences, vector<vector<int>>& edges) //Обработка данных из дерева
{
	vector<pnode> nodes(k); //Создадим вектор узлов
	int n = (k + 1) / 2;

	for (int i = 0; i < k; i++)
		nodes[i] = nullptr; //Пока все узлы пустые
	for (int i = 0; i < k - 1; i++)
	{
		if (!nodes[edges[i][0]]) //Проверяем, не создан ли уже этот узел
		{
			vector<set<char>> set_data(0); //Пока set_data пусто
			
			if (edges[i][0] >= k - n) //Если лист является узлом, то заполняем set_data последовательностью из файла
			{
				set<char> tmp;
				for (int m = 0; m < q; m++)
				{
					tmp = { sequences[edges[i][0] - (k - n)][m] };
					set_data.push_back(tmp);
				}
			}

			nodes[edges[i][0]] = new Node(set_data, nullptr, nullptr, nullptr, edges[i][0], 0, q);  //Создаем новый узел дерева, число number - номер узла

		}

		if (!nodes[edges[i][1]]) //Проверяем, не создан ли уже этот узел
		{
			vector<set<char>> set_data(0); //Пока set_data пусто

			if (edges[i][1] >= k - n) //Если лист является узлом, то заполняем set_data последовательностью из файла
			{
				set<char> tmp;
				for (int m = 0; m < q; m++)
				{
					tmp = { sequences[edges[i][1] - (k - n)][m] };
					set_data.push_back(tmp);
				}
			}

			nodes[edges[i][1]] = new Node(set_data, nodes[edges[i][0]], nullptr, nullptr, edges[i][1], 0, q); //Создаем новый узел дерева, число number - номер узла
		}

		//Заполним листья у leaves

		if (!nodes[edges[i][0]]->lt)
			nodes[edges[i][0]]->lt = nodes[edges[i][1]];
		else
			nodes[edges[i][0]]->rt = nodes[edges[i][1]];
	}

	BSTree res(nodes[0]);

	return res;
}

BSTree build_trees(string filename) //Построение дерева
{
	int q, k;
	vector<char*> sequences(1);
	vector<vector<int>> edges(1);

	read_from_file(filename, q, k, sequences, edges);
	return build_tree(q, k, sequences, edges);
}

void print_tree_file(ostream& out, pnode node, int pos, int q)
{


	if (node == nullptr)
	{
		for (int i = 0; i < pos; i++)
			out << "     ";
		out << "  " << endl;
		return;
	}


	print_tree_file(out, node->rt, pos + 1, q);

	for (int i = 0; i < pos; i++)
		out << "     ";

	if (node->root && ((node->depth - node->root->depth) > 1))
		out << "        ";
	for (int i = 0; i < q; i++)
		for (auto j : node->set_data[i])
			out << j;

	print_tree_file(out, node->lt, pos + 1, q);

}

