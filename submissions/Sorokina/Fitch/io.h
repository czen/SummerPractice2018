#pragma once
#include "tree.h"
#include <vector>

//Ввод данных дерева из файла
void read_from_file(string filename, int& q, int& k, vector<char*>& sequences, vector<vector<int>>& edges);

//Обработка данных из файла
BSTree build_tree(int q, int k, vector<char*>& sequences, vector<vector<int>>& edges);

//Построение дерева
BSTree build_trees(string filename);

//Запись данных результата в файл
void print_tree_file(ostream& out, pnode node, int pos, int q);