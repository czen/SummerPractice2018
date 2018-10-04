#pragma once
#include <iostream>
#include "io.h"

//������� ���������� ����������� �������� � ���������� ���� char
set<char> set_intersection(set<char> set1, set<char> set2);

//������� ���������� ����������� �������� � ���������� ���� char
set<char> set_union(set<char> set1, set<char> set2);

//������ ����� ���������� ��������� ����� ����� ��������. ��������� ������ ������ "������ ����" 
void up_down(pnode node, int k);

//������ ����� ���������� ��������� ����� ����� ��������. ��������� ������ ������ "����� �����" 
void fitch(pnode root, int q, int n, int& c);

