#pragma once
#include <iostream>
#include "io.h"

//Функция нахождения пересечения множеств с элементами типа char
set<char> set_intersection(set<char> set1, set<char> set2);

//Функция нахождения объединения множеств с элементами типа char
set<char> set_union(set<char> set1, set<char> set2);

//Вторая часть реализации алгоритма Фитча через рекурсию. Процедура обхода дерева "сверху вниз" 
void up_down(pnode node, int k);

//Первая часть реализации алгоритма Фитча через рекурсию. Процедура обхода дерева "снизу вверх" 
void fitch(pnode root, int q, int n, int& c);

