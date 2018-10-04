#include <iostream>
#include <ctime>
#include "NameFunction.h"

using namespace std;

int main(int argec, char* argv[]) {
    int len[3]; // массив для длинн строк в файле
    string term1, term2, sum, res;//строки с зашифрованными операндами и результатом сложения
    unsigned int start_time =  clock(); // начальное время

    input_data( argv[1], len, term1, term2, sum);

    int lit_amount = 0;
    string unicstring;
    NumberOfLetters(term1, term2, sum, lit_amount,
            unicstring);//конкатенация строк и подсчет количества уникальных букв

    int *work = new int[lit_amount];
    string result_str="_";
    Gen(0, -1, work, lit_amount, term1, term2, sum,
            len, unicstring, result_str);//генератор сочетаний

    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    out_data( argv[2], result_str, search_time);

    //system("pause");
    return 0;
}