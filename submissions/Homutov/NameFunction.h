//
// Created by ADMIN on 11.08.2018.
//
#ifndef SUMMERPRCTICE_NAMEFUNCTION_H
#define SUMMERPRCTICE_NAMEFUNCTION_H

#include <string>

using namespace std;

void permutation(int *m, int l, int unic_amount, string term1, string term2,
                 string sum, int *len, string uniqstr, string &result);

void Gen(int lvl, int vmax, int *arr, int liters, string t1, string t2,
         string s, int *leng, string uni, string &res);

void input_data(const char *filename, int *amount, string &term1,
                string &term2, string &sum);

void out_data(const char *filename, string str, int timer);

void NumberOfLetters(string term1, string term2, string sum,
                     int &count, string &uniqstr);

#endif //SUMMERPRCTICE_NAMEFUNCTION_H
