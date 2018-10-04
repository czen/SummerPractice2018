#pragma once
#include "io.h"
#include <stack>
#include <set>
#include "fitch.h"

//������ ����� ���������� ��������� ����� ����� ����. ��������� ������ ������ "����� �����"
void up_down_st1(pnode node, int n, int q, int& c); 

//��������� ���������� ������� �������� ����� �������� ��������� �������. ����������� �� ������ ����� ��������� ��� ��������� ����� ������
void fill_set_data(vector<set<char>>& data);

//������ ����� ���������� ��������� ����� ����� ����. ��������� ������ ������ "������ ����"
void up_down_st2(pnode node);




