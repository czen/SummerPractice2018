#pragma once
#include "tree.h"
#include <vector>

//���� ������ ������ �� �����
void read_from_file(string filename, int& q, int& k, vector<char*>& sequences, vector<vector<int>>& edges);

//��������� ������ �� �����
BSTree build_tree(int q, int k, vector<char*>& sequences, vector<vector<int>>& edges);

//���������� ������
BSTree build_trees(string filename);

//������ ������ ���������� � ����
void print_tree_file(ostream& out, pnode node, int pos, int q);