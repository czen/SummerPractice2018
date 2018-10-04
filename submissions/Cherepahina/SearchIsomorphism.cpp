// SearchIsomorphism.cpp: определяет точку входа для консольного приложения.
//
#include <stdio.h>
//   #include <tchar.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue> 
#include <stack>
#include <ctime>
#include <iomanip>

using namespace std;
										
// возвращает вектор, элементы которого количество вершин относительно количества ребер
vector<int> CountEdges(vector<string> G, int m) {
	vector<int> Edges(m, 0);
	vector<int> CountEdg(m, 0);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (G[i][j] == '1' && i != j) {
				++Edges[i];
			}
		}
	}
	int j;
	for (int i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			if (Edges[i] == j) {
				CountEdg[j]++;
			}
		}
		
	}
	return CountEdg;
}
// возвращает вектор, элементы которого количество вершин относительно количества ребер
// функция переопределена для входных данных из массива, который формируется при поиске подграфа
vector<int> CountEdges(vector<string> G, int m, int *a) {
	vector<int> Edges(m, 0);
	vector<int> CountEdg(m, 0);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (G[a[i]][a[j]] == '1' && i != j) {
				Edges[i]++;
			}
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (Edges[i] == j) {
				++CountEdg[j];
			}
		}
	}
	return CountEdg;
}

// сочетание без перестановки для поиска подграфа в графе
bool GenerateCombination(int *a, int n, int m)
{
	int k = m;
	for (int i = k - 1; i >= 0; --i)
		if (a[i] < n - k + i + 1)
		{
			++a[i];
			for (int j = i + 1; j < k; ++j)
				a[j] = a[j - 1] + 1;
			return true;
		}
	return false;
}
// проверка на изморфность графов с помощью очереди
bool IsIsomorphismStack(vector<string> adjArr1, int n, vector<int> Edges2, int m, int *combination)
{
	stack<bool> Stack;
	Stack.push(1);
	while (Stack.top())
	{ 
		Stack.pop();
		vector<int> Edges1(n);				// вектор, элементы которого количество вершин относительно количества ребер
		Edges1 = CountEdges(adjArr1, m, combination);
		if (Edges1 == Edges2) {
			Edges1.clear();
			return true;
		}
		Stack.push(!GenerateCombination(combination, n, m));
	}
	return false;
}

// проверка на изморфность графов рекурсивно
bool IsIsomorphismRecursive(vector<string> adjArr1, int n, vector<int> Edges2, int m, int *combination)
{
	vector<int> Edges1(n);							// вектор, элементы которого количество вершин относительно количества ребер
	Edges1 = CountEdges(adjArr1, m, combination);
	if (Edges1 == Edges2) {
			Edges1.clear();
		return true;
	}else{
		Edges1.clear();
		if (!GenerateCombination(combination, n, m)) {
			IsIsomorphismRecursive(adjArr1, n, Edges2, m, combination);
		}
		else {
			return false;
		}
		
	}
	return false;
}
// проверка на изморфность графов с помощью очереди
bool IsIsomorphismQueue(vector<string> adjArr1, int n, vector<int> Edges2, int m, int *combination)
{
	queue<bool> Queue;
	Queue.push(1);									
	while (Queue.front())
	{ 
		Queue.pop();
		vector<int> Edges1(n);				// вектор, элементы которого количество вершин относительно количества ребер
		Edges1 = CountEdges(adjArr1, m, combination);
		if (Edges1 == Edges2) {
			return true;
		}
		Queue.push(!GenerateCombination(combination, n, m));
	}

	return false;
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	double startTime = 0, endTime = 0;								// время

	string filename;
	if (argc > 1)								// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
		filename = argv[1];
	else
		filename = "input.txt";
	ifstream in(filename.c_str());
	int n1, n2;									// количество вершин матриц смежности
	if (!in.is_open())
	{
		cout << "Не удается открыть файл!" << endl;
	}
	else {
		in >> n1;								// количество вершин матрицы смежности 1
		vector<string> adjArr1(n1);				// вектор смежности 1
		for (int i = 0; i < n1; ++i)
			in >> adjArr1[i];
		in >> n2;								// количество вершин матрицы смежности 2
		vector<string> adjArr2(n2);				// вектор смежности 2
		for (int i = 0; i < n2; ++i)
			in >> adjArr2[i];
		in.close();

		int *combination = new int[n2];			// матрица комбинаций для перебора сочетаний 
		for (int i = 0; i < n2; i++)
			combination[i] = i;

		vector<int> Edges(n2);					// вектор, элементы которого количество вершин относительно количества ребер
		Edges = CountEdges(adjArr2, n2);

		ofstream out("output.txt");
		out << "1. Рекурсивный поиск изоморфности " << endl;
		startTime = clock();
		// Рекурсивный поиск изоморфности
		if (IsIsomorphismRecursive(adjArr1, n1, Edges, n2, combination))
			out << "Подграф изоморфен!" << endl;
		else
			out << "Подграф НЕ изоморфен!" << endl;
		endTime = clock();
		out << "Время выполнения: " << fixed << setprecision(3)
			<< 1000.0 * (endTime - startTime)/ CLOCKS_PER_SEC 
			<< " ms" << endl << endl;

		// Поиск изоморфности с помощью очереди
		out << "2. Поиск изоморфности с помощью очереди " << endl;
		// пересоздаем массив первой комбинации сочетаний
		for (int i = 0; i < n2; i++)
			combination[i] = i;

		startTime = clock();
		if (IsIsomorphismQueue(adjArr1, n1, Edges, n2, combination))
			out << "Подграф изоморфен!" << endl;
		else
			out << "Подграф НЕ изоморфен!" << endl;	
		endTime = clock();
		out << "Время выполнения: " << fixed << setprecision(3) 
			<< 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC 
			<< " ms" << endl << endl;

		// Поиск изоморфности через стек
		out << "3. Поиск изоморфности через стек " << endl;
		// пересоздаем массив первой комбинации сочетаний
		for (int i = 0; i < n2; i++)
			combination[i] = i;

		startTime = clock();
		if (IsIsomorphismStack(adjArr1, n1, Edges, n2, combination)) {
			out << "Подграф изоморфен!" << endl;
		}
		else {
			out << "Подграф НЕ изоморфен!" << endl;
		}
		endTime = clock();
		out << "Время выполнения: " << fixed << setprecision(3)
			<< 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC
			<< " ms" << endl << endl;
		out << "Таблица смежности графа порядка " << n1 << endl;
		out << "Таблица смежности подграфа порядка " << n2 << endl;
		out.close();

	}
    return 0;
}

