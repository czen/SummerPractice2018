#pragma once
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Node;

typedef Node* pnode;

class Node //����� ���� ��������� ������
{
public:
	vector< set<char> > set_data; //������ �������� �������� �������������������
	pnode root; //������ ����
	pnode lt, rt; // ������� ����
	int number; //����� �������
	int depth; //������� ����
	int length; //����� �������������������
	vector<int> set_unions; //������� ���������� �������� ����������� ��� ����������� �����,
	                        //������������ � ���������� �� ������ ��� ���������� ��������� ������
	
	Node() //����������� ��� ����������
	{ 
		set_data = vector< set<char> >();
		root = nullptr; 
		rt = nullptr; 
		lt = nullptr;
		number = 0;
		length = 0;
	}
	
	//����������� � �����������
	Node (vector< set<char> > a, pnode root = nullptr, pnode t1 = nullptr, pnode t2 = nullptr, int num = 0, int depth = 0, int length = 0) :
		root(root), lt(t1), rt(t2), number(num), depth(depth), length(length)
	{
		set_data = vector< set<char> >();
		for (int i = 0; i < a.size(); i++)
			set_data.push_back(a[i]);

		set<char> tmp;
		if (set_data.size() < length)
			for (int i = 0; i < length - a.size(); i++)
				set_data.push_back(tmp);
		for (int i = 0; i < length; i++)
			set_unions.push_back(0);
	}
};


//����� �������� ������ ������
class BSTree { 
public:
	pnode	root; //������ ������

	void	printPref(pnode	&t); //������ ������ �� �����

	//����������� ��� ����������
	BSTree() { root = 0; }

	//����������� � ����������
	BSTree(pnode root) {
		this->root = root;
	}

	void	printPref()
	{
		printPref(root);
	}  
};

//��������� ���������� ������� ������-��������. ����������� ��� �������� ����������� ����� �������
void output_tree(pnode node, vector<pnode>& vec, int depth = 1);

//����� ������ � �����
void print_tree(pnode node, int pos, int q);