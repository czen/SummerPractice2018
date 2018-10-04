#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

/*Текущий результат количества ребер подграфа*/
	int TRes = 0;
/*---*/


/*-ВСПОМОГАТЕЛЬНЫЕ-ФУНКЦИИ-ПРОГРАММЫ-------------------------------------------------------------------------------------*/
/*Функция рекурсии*/

	/*Рекурсия вызывает себя со сдвигом.За счёт сдвига и цикла получаются комбинации в массиве xG.
	Это комбинации вершин подграфа.По матрице смежности подсчитывается, количество ребер между этими вершинами,
	т.е.можно ли из одной вершины попасть в другую.
	Сравнивается с результирующим значением, если новое значение больше, то происходит замена результирующего.
	В итоге у нас вершины с наибольшим количеством ребер между вершинами.*/

	void fRecursion(int *xG, int vG, int eG, int **mG, int *Res, int l = -1)
	//Параметры - матрица перебора, количество вершин подграфа, количество вершин графа, 
	//матрица смежности графа, результат массив с вершинами, счетчик
	{
		if (l == vG - 1)
		{
			/*Проверка комбинаций вершин подграфа*/
			
				for (int i = 0; i < vG; i++)
					cout << xG[i] + 1 << " ";
				cout << "\n";
			
			/*---*/
			/*Суммирование ребер вершин подграфа по матрице смежности*/
				int SRes = 0;
				for (int i = 0; i < vG - 1; i++)
					for (int j = i + 1; j < vG; j++)
						SRes += mG[xG[i]][xG[j]];
			/*---*/
			/*Если текущий результат больше результирующего, то изменяем значение результирующего на текущий*/
				if (SRes > TRes)
				{
					for (int i = 0; i < vG; i++)
						Res[i] = xG[i] + 1;
					TRes = SRes;
				};
			/*---*/
		}
		else
		{
			/*Составлений комбинаций вершин подграфа*/
				for (int i = 0; i < eG; i++)
				{
					xG[l + 1] = i;
					if ((l > -1) && (xG[l + 1] > xG[l]))
						fRecursion(xG, vG, eG, mG, Res, l + 1);
					else if (l == -1)
						fRecursion(xG, vG, eG, mG, Res, l + 1);
				};
			/*---*/
		};
	};
/*---*/




/*Стек и операции над ним*/
	struct Stack
	{
		/*Сумма ребер вершин подграфа*/
		int SRes;
		/*---*/
		/*Массив вершин подграфа*/
			int *xG;
		/*---*/
		/*Ссылка на предыдущий элемент стека*/
			Stack *prev;
		/*---*/
	} *stackTOP; //Вершина стека

	/*Создание элемента*/
		void StackCreate(int *xG, int vG, int SRes)
		{
			Stack *temp = new Stack;
			temp->SRes = SRes;
			temp->xG = new int[vG];
			for (int i = 0; i < vG; i++)
				temp->xG[i] = xG[i];
			temp->prev = NULL;
			stackTOP = temp;
		};
	/*---*/

	/*Добавление элемента*/
		void StackAdd(int *xG, int vG, int SRes)
		{
			Stack *temp = new Stack;
			temp->SRes = SRes;
			temp->xG = new int[vG];
			for (int i = 0; i < vG; i++)
				temp->xG[i] = xG[i];
			temp->prev = stackTOP;
			stackTOP = temp;
		};
	/*---*/

	/*Удаление элемента*/
		void StackDelete()
		{
			Stack *temp = new Stack;
			temp = stackTOP->prev;
			stackTOP = NULL;
			stackTOP = temp;
		};
	/*---*/

	/*Функция стека*/

		/*За счёт модифицированного пузырька происходит перебор всех комбинаций для заданного количества вершин подграфа.
		По матрице смежности производится подсчет ребер между этими вершинами. Сумма и вершины записываются в стек как элемент. 
		После того как в стеки окажутся все такие элементы, их суммы сравниваются и элементы удаляются, 
		остаётся лишь одна комбинация с наибольшим количеством ребер между вершинами.*/
		

		void fStack(int vG, int eG, int **mG, int *Res)
		{
			/*Массив перебора - массив вершин подграфа*/
				int *xG = new int[eG];
				for (int i = 0; i < eG; i++)
					xG[i] = i;
			/*---*/

			/*Проверка комбинаций вершин подграфа - 1 часть*/
			
				for (int j = 0; j < vG; j++)
					cout << xG[j] + 1 << " ";
				cout << "\n";
			
			/*---*/

			/*Суммирование ребер вершин подграфа по матрице смежности занесение ее в стек - 1 часть*/
				int SRes = 0;
				for (int xi = 0; xi < vG - 1; xi++)
					for (int xj = xi + 1; xj < vG; xj++)
						SRes += mG[xG[xi]][xG[xj]];
				StackCreate(xG, vG, SRes);
			/*---*/

			/*Составлений комбинаций вершин подграфа*/
				bool ret = true;
				while (ret == true)
				{
					for (int i = vG - 1; i >= 0; --i)
						if (xG[i] < eG - vG + i)
						{
							++xG[i];
							for (int j = i + 1; j < vG; ++j)
								xG[j] = xG[j - 1] + 1;

							/*Суммирование ребер вершин подграфа по матрице смежности занесение ее в стек - 2 часть*/
								int SRes = 0;
								for (int xi = 0; xi < vG - 1; xi++)
									for (int xj = xi + 1; xj < vG; xj++)
										SRes += mG[xG[xi]][xG[xj]];
								StackAdd(xG, vG, SRes);
							/*---*/

							/*Проверка комбинаций вершин подграфа - 2 часть*/
							
								for (int j = 0; j < vG; j++)
									cout << xG[j] + 1 << " ";
								cout << "\n";
							
							/*---*/

							ret = true;
							break;
						}
						else
							ret = false;
				};
			/*---*/

			/*Если текущий результат в вершине стека больше результирующего, то изменяем значение результирующего на текущий. Удаляем вершину.*/
				while (stackTOP != NULL)
				{
					if (stackTOP->SRes > TRes)
					{
						for (int i = 0; i < vG; i++)
							Res[i] = stackTOP->xG[i] + 1;
						TRes = stackTOP->SRes;
					};
					StackDelete();
				};
			/*---*/
		};
	/*---*/
/*---*/





/*Очередь и операции над ней*/
	struct Queue
	{
		/*Сумма ребер вершин подграфа*/
		int SRes;
		/*---*/
		/*Массив вершин подграфа*/
		int *xG;
		/*---*/
		/*Ссылка на следующий элемент очереди*/
			Queue *next;
		/*---*/
	} *queueBOTTOM; //Первый элемент очереди

	/*Создание элемента*/
		void QueueCreate(int *xG, int vG, int SRes)
		{
			Queue *temp = new Queue;
			temp->SRes = SRes;
			temp->xG = new int[vG];
			for (int i = 0; i < vG; i++)
				temp->xG[i] = xG[i];
			temp->next = NULL;
			queueBOTTOM = temp;
		};
	/*---*/

	/*Добавление элемента*/
		void QueueAdd(int *xG, int vG, int SRes)
		{
			Queue *temp = new Queue;
			temp = queueBOTTOM;
			while (temp->next != NULL)
			{
				temp = temp->next;
			};
			Queue *qnew = new Queue;
			qnew->SRes = SRes;
			qnew->xG = new int[vG];
			for (int i = 0; i < vG; i++)
				qnew->xG[i] = xG[i];
			qnew->next = NULL;
			temp->next = qnew;
		};
	/*---*/

	/*Удаление элемента*/
		void QueueDelete()
		{
			Queue *temp = new Queue;
			temp = queueBOTTOM->next;
			queueBOTTOM = NULL;
			queueBOTTOM = temp;
		};
	/*---*/

	/*Функция очереди*/

		/*За счёт модифицированного пузырька происходит перебор всех комбинаций для заданного количества вершин подграфа. 
		По матрице смежности производится подсчет ребер между этими вершинами. Сумма и вершины записываются в очередь как элемент.
		После того как в очереди окажутся все такие элементы, их суммы сравниваются и элементы удаляются,
		остаётся лишь одна комбинация (элемент очереди) с наибольшим количеством ребер между вершинами.*/


		void fQueue(int vG, int eG, int **mG, int *Res)
		{
			/*Массив перебора - массив вершин подграфа*/
				int *xG = new int[eG];
				for (int i = 0; i < eG; i++)
					xG[i] = i;
			/*---*/

			/*Проверка комбинаций вершин подграфа - 1 часть*/
			
				for (int j = 0; j < vG; j++)
					cout << xG[j] + 1 << " ";
				cout << "\n";
			
			/*---*/

			/*Суммирование ребер вершин подграфа по матрице смежности занесение ее в очередь - 1 часть*/
				int SRes = 0;
				for (int xi = 0; xi < vG - 1; xi++)
					for (int xj = xi + 1; xj < vG; xj++)
						SRes += mG[xG[xi]][xG[xj]];
				QueueCreate(xG, vG, SRes);
			/*---*/

			/*Составлений комбинаций вершин подграфа*/
				bool ret = true;
				while (ret == true)
				{
					for (int i = vG - 1; i >= 0; --i)
						if (xG[i] < eG - vG + i)
						{
							++xG[i];
							for (int j = i + 1; j < vG; ++j)
								xG[j] = xG[j - 1] + 1;

							/*Суммирование ребер вершин подграфа по матрице смежности занесение ее в очередь - 2 часть*/
								int SRes = 0;
								for (int xi = 0; xi < vG - 1; xi++)
									for (int xj = xi + 1; xj < vG; xj++)
										SRes += mG[xG[xi]][xG[xj]];
								QueueAdd(xG, vG, SRes);
							/*---*/

							/*Проверка комбинаций вершин подграфа - 2 часть*/
							
								for (int j = 0; j < vG; j++)
									cout << xG[j] + 1 << " ";
								cout << "\n";
							
							/*---*/

							ret = true;
							break;
						}
						else
							ret = false;
				};
			/*---*/

			/*Если текущий результат у первого элемента очереди больше результирующего, то изменяем значение результирующего на текущий. Удаляем первый элемент.*/
				while (queueBOTTOM != NULL)
				{
					if (queueBOTTOM->SRes > TRes)
					{
						for (int i = 0; i < vG; i++)
							Res[i] = queueBOTTOM->xG[i] + 1;
						TRes = queueBOTTOM->SRes;
					};
					QueueDelete();
				};
			/*---*/
		};
	/*---*/
/*---*/
/*-ВСПОМОГАТЕЛЬНЫЕ-ФУНКЦИИ-ПРОГРАММЫ-------------------------------------------------------------------------------------*/





int main()
{
	/*Открываем файлы для чтения и для записи*/
		ifstream input("input.txt");
		ofstream output("output.txt");
	/*---*/

	/*Количество вершин подграфа, Количество вершин графа, Матрица смежности*/
		int vG;
		int eG;
		int **mG;
	/*---*/

	/*Чтение - Количество вершин подграфа, Количество вершин графа, Пара вершин ребра*/
		input >> vG;
		input >> eG;
		mG = new int*[eG];
		for (int i = 0; i < eG; i++)
			mG[i] = new int[eG];
		for (int i = 0; i < eG; i++)
			for (int j = 0; j < eG; j++)
				input >> mG[i][j];
	/*---*/

	/*Меню выбора метода*/
		int choose;
		cout << "Choose method:\n";
		cout << "1. Recursion.\n";
		cout << "2. Stack.\n";
		cout << "3. Queue.\n";
		cin >> choose;
	/*---*/

	/*Проверка выбранного метода*/
		/*Рекурсия*/
			if (choose == 1)
			{
				/*Результирующий результат, Массив перебора - массивы вершин подграфа*/
					int *Res = new int[vG];
					int *xG = new int[vG];
				/*---*/
				/*Засекаем время*/
					unsigned int time = clock();
				/*---*/
					/*Вызов функции рекурсии и передача данных в результат*/
						fRecursion(xG, vG, eG, mG, Res); 
					/*---*/
				/*Подсчет времени работы алгоритма и вывод*/
					cout << (clock() - time) / 1000.0 << " sec.\n";
				/*---*/
				/*Вывод результата*/
					for (int i = 0; i < vG; i++)
						output << Res[i] << " ";
					output << "(" << TRes << ")";
				/*---*/
			}
		/*---*/
		/*Стек*/
			else if (choose == 2)
			{
				/*Результат - массив вершин подграфа*/
				int *Res = new int[vG];
				/*---*/
				/*Засекаем время*/
					unsigned int time = clock();
				/*---*/
					/*Вызов функции стека и передача данных в результат*/
						fStack(vG, eG, mG, Res);
					/*---*/
				/*Подсчет времени работы алгоритма и вывод*/
					cout << (clock() - time) / 1000.0 << " sec.\n";
				/*---*/
				/*Вывод результата*/
					for (int i = 0; i < vG; i++)
						output << Res[i] << " ";
					output << "(" << TRes << ")";
				/*---*/
			}
		/*---*/
		/*Очередь*/
			else if (choose == 3)
			{
				/*Результат - массив вершин подграфа*/
				int *Res = new int[vG];
				/*---*/
				/*Засекаем время*/
					unsigned int time = clock();
				/*---*/
					/*Вызов функции очереди и передача данных в результат*/
						fQueue(vG, eG, mG, Res);
					/*---*/
				/*Подсчет времени работы алгоритма и вывод*/
					cout << (clock() - time) / 1000.0 << " sec.\n";
				/*---*/
				/*Вывод результата*/
					for (int i = 0; i < vG; i++)
						output << Res[i] << " ";
					output << "(" << TRes << ")";
				/*---*/
			};
		/*---*/
	/*---*/

	/*Закрываем файл для чтения и для записи*/
		input.close();
		output.close();
	/*---*/

	/*Пауза в консоле*/
		system("pause");
	/*---*/
};