#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string.h>
#include <ctime>
#include <cmath>

using namespace std;
ofstream fout;
char chars[] = { '0','1','2','3','4','5','6','7','8','9' };//цифры, которые нужны для перебора
//функция для нахождения букв в строке
int findPosNotInt(string &s)
{
	for (int i = 0; i<s.length(); i++) {
		if ((s[i]<'0' || s[i]>'9') && s[i] != '|' && s[i] != '=') {
			return i;
		}
	}
	return -1;
}

//функция для замены букв на цифры
string replaceAll(string str, char what, char by)
{
	string temp = str;
	for (int i = 0; i<str.length(); i++) {
		if (temp[i] == what) temp[i] = by;
	}
	return temp;
}
//флаг для проверки повторных символов
bool contain(string &s, char c)
{
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == c) return true;
	}
	return false;
}
//функция для определния делимого, делителя и частного
void splitter(string &s, string &s1, string &s2, string &s3)
{
	int switcher = 0;
	for (auto i = 0; i<s.length(); i++) {
		if (s[i] == '|') switcher++;
		if (s[i] == '=') switcher++;
		if (switcher == 0 && s[i] != '|' && s[i] != '=') {
			s1 += s[i];
		}
		if (switcher == 1 && s[i] != '|' && s[i] != '=') {
			s2 += s[i];
		}
		if (switcher == 2 && s[i] != '|' && s[i] != '=') {
			s3 += s[i];
		}
	}
}
//функция для вывода данных в файл
void writeInFile(float a, float b, float c) {
	fout.open("out.txt", ios_base::app);
	fout << a << "|" << b << "=" << c << endl;
	fout.close();
}

//функция поиска подходящих значений методом перебора
void recTask(string s1) 
{ 
	int k = findPosNotInt(s1); 
	if (k != 0 && k != -1) { 
		for (int i = 0; i < 10; i++) { 
			if (!contain(s1, chars[i])) { 
				recTask(replaceAll(s1, s1[k], chars[i])); 
			} 
		} 
	} 
	if (k == 0) { 
		for (int i = 1; i < 10; i++) { 
			if (!contain(s1, chars[i])) { 
				recTask(replaceAll(s1, s1[k], chars[i])); 
			} 
		} 
	} 
	if (k == -1) { 
		string s1s = ""; 
		string s2s = ""; 
		string s3s = ""; 
		splitter(s1, s1s, s2s, s3s); 
		if (s2s[0] == 0) 
			 s2s = "0"; 
			float a, b, c; 
			a = atof(s1s.c_str()); 
			b = atof(s2s.c_str()); 
			c = atof(s3s.c_str()); 
			if (b != 0) { 
				if (fabs((a / b) - c) < 1E-6) { 
					writeInFile(a, b, c); 
				} 
				else return; 
			}
	} 
} 


int main(int argc, char *argv[])
{
	char ask[50];
	remove("out.txt");
	ifstream fin("in.txt"); // открыли файл для чтения
	if (!fin.is_open()) // если файл не открыт
		cout << "Couldn't open file!\n"; // сообщить об этом
	else
		fin.getline(ask, 50);
	fin.close();
	recTask(ask);
	fstream fout("out.txt");
	if (fout.peek() == EOF) cout << "Wrong data!!!\n";
	else
	cout << "Results in file out.txt\n";
	cout << "runtime = " << clock() / 1000.0 << endl;
	return 0;
}
