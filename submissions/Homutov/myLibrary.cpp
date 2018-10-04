//
// Created by ADMIN on 16.08.2018.
//
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "NameFunction.h"

using namespace std;

// всевозможные перестановки массива и их обработка
// l = 0
// n - количество уникальных букв
void permutation(int *m, int l, int unic_amount, string term1, string term2,
        string sum, int *len, string uniqstr, string &result)
{
    if( l==unic_amount-1 ) {
        for( int i=0; i < unic_amount; i++){
            for (int g=0; g < 3; g++) { //определяем, какую строку обработать
                if(g==0){
                    for (int j = 0; j < len[g]; ++j) {// для каждого элем term1
                        for (int k = 0; k < unic_amount; k++) { // проходим по уник буквам
                            if (term1[j]== uniqstr[k]) { // заменяем буквы на цифры
                                term1[j] = 48 + m[k];
                             }
                        }
                    }
                }
                if(g==1){
                    for (int j = 0; j < len[g]; ++j) {// для каждого элем term2
                        for (int k = 0; k < unic_amount; k++) { // проходим по уник буквам
                            if (term2[j]== uniqstr[k]) {
                                term2[j]= 48 + m[k];
                            }
                        }
                    }
                }
                if(g==2){
                    for (int j = 0; j < len[g]; ++j) {// для каждого элем sum
                        for (int k = 0; k < unic_amount; k++) { // проходим по уник буквам
                            if (sum[j]== uniqstr[k]) {
                                sum[j]= 48 + m[k];
                            }
                        }
                    }
                }
            }
            int term1_n =  atoi(term1.c_str());
            int term2_n =  atoi(term2.c_str());
            int sum_n =  atoi(sum.c_str());
            if ( term1_n + term2_n == sum_n ) {
                result="result";
                result = term1+"+"+term2+"="+sum;

            }
        }
    }
    else {
        for( int i = l; i < unic_amount; i++ ) {
            int tmp = m[l];
            m[l] = m[i];
            m[i] = tmp;
            permutation( m, l+1, unic_amount, term1, term2, sum, len, uniqstr, result);
            tmp = m[l];
            m[l] = m[i];
            m[i] = tmp;
        }
    }
}

// генератор сочетаний
// lvl = 0, vmax = -1
void Gen(int lvl, int vmax, int *arr, int liters, string t1, string t2,
        string s, int *leng, string uni, string &res)
{
        if(lvl >= liters) {
            for(int i = 0; i < liters; ++i)
                permutation(arr, 0, liters, t1, t2, s, leng, uni, res);
        }
        else {
            for(int j = vmax + 1; j <= 9; ++j) {
                arr[lvl] = j;
                Gen(lvl + 1, j, arr, liters, t1, t2, s, leng, uni, res);
            }
        }
}

// ввод данных из файла
// amount - длина соответствующей строки
void input_data(const char *filename, int *amount, string &term1,
                string &term2, string &sum)
{
    assert(filename != NULL); // проверка на ввод имени файла
    ifstream fin(filename);
    if (!fin.is_open()) throw "File not found!";
    string s = "_"; // сюда будем класть считанные строки
    try {
        for (int i = 0; i < 3; i++) {
            if (s == "") throw 100500;
            getline(fin, s);
            amount[i] = s.size(); // запоминаем размер строки
            if (i == 0) term1 = s; // запоминаем строки
            if (i == 1) term2 = s;
            else sum = s;
        }
    }
    catch (int){
        cout << "ERROR: a lack of data in " << filename << endl;
    }
    fin.close();
}

// вывод данных в файл
void out_data(const char *filename, string str, int timer) {
    ofstream fout(filename);
    if(str == "_")
        fout << "Bad data!";
    else
        fout << str;
    fout << '\n';
    fout << "Runtime: " << timer << " mls";
    fout.close();
}

// конкатенация строк и подсчет количества уникальных букв
// count - количество уникальных букв
// uniqstr - массив уникальных букв
void NumberOfLetters(string term1, string term2, string sum,
        int &count, string &uniqstr)
{
    uniqstr = "";
    string monostr = term1 + term2 + sum;
    int k = monostr.size(); // размер конкатенированной строки
    char *writable = new char[k + 1];
    copy(monostr.begin(), monostr.end(), writable);
    writable[k] = '\0';
    char *litstr = new char[k]; // строка для потсчета уникальных букв
    bool flag = true; // если буква уникальная - true
    litstr[0] = writable[0]; // пусть первая буква уникальна
    uniqstr = uniqstr + writable[0];
    count = 1;
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < i; j++)
            if (litstr[j] == writable[i]) flag = false;//если буква не уникальна
        if (flag){
            litstr[i] = writable[i];
            count++;
            uniqstr = uniqstr + writable[i];
        }
        else flag = true;
    }
    delete[] writable;
    delete[] litstr;
}
