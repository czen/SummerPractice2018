#pragma once
#include "io.h"
#include <stack>
#include <set>
#include "fitch.h"

//Первая часть реализации алгоритма Фитча через стек. Процедура обхода дерева "снизу вверх"
void up_down_st1(pnode node, int n, int q, int& c); 

//Процедура заполнения вектора множеств одним символом случайным образом. Применяется во второй части алгоритма для обработки корня дерева
void fill_set_data(vector<set<char>>& data);

//Вторая часть реализации алгоритма Фитча через стек. Процедура обхода дерева "сверху вниз"
void up_down_st2(pnode node);




