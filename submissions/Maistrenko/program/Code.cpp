#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

/*������� ��������� ���������� ����� ��������*/
	int TRes = 0;
/*---*/


/*-���������������-�������-���������-------------------------------------------------------------------------------------*/
/*������� ��������*/

	/*�������� �������� ���� �� �������.�� ���� ������ � ����� ���������� ���������� � ������� xG.
	��� ���������� ������ ��������.�� ������� ��������� ��������������, ���������� ����� ����� ����� ���������,
	�.�.����� �� �� ����� ������� ������� � ������.
	������������ � �������������� ���������, ���� ����� �������� ������, �� ���������� ������ ���������������.
	� ����� � ��� ������� � ���������� ����������� ����� ����� ���������.*/

	void fRecursion(int *xG, int vG, int eG, int **mG, int *Res, int l = -1)
	//��������� - ������� ��������, ���������� ������ ��������, ���������� ������ �����, 
	//������� ��������� �����, ��������� ������ � ���������, �������
	{
		if (l == vG - 1)
		{
			/*�������� ���������� ������ ��������*/
			
				for (int i = 0; i < vG; i++)
					cout << xG[i] + 1 << " ";
				cout << "\n";
			
			/*---*/
			/*������������ ����� ������ �������� �� ������� ���������*/
				int SRes = 0;
				for (int i = 0; i < vG - 1; i++)
					for (int j = i + 1; j < vG; j++)
						SRes += mG[xG[i]][xG[j]];
			/*---*/
			/*���� ������� ��������� ������ ���������������, �� �������� �������� ��������������� �� �������*/
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
			/*����������� ���������� ������ ��������*/
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




/*���� � �������� ��� ���*/
	struct Stack
	{
		/*����� ����� ������ ��������*/
		int SRes;
		/*---*/
		/*������ ������ ��������*/
			int *xG;
		/*---*/
		/*������ �� ���������� ������� �����*/
			Stack *prev;
		/*---*/
	} *stackTOP; //������� �����

	/*�������� ��������*/
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

	/*���������� ��������*/
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

	/*�������� ��������*/
		void StackDelete()
		{
			Stack *temp = new Stack;
			temp = stackTOP->prev;
			stackTOP = NULL;
			stackTOP = temp;
		};
	/*---*/

	/*������� �����*/

		/*�� ���� ����������������� �������� ���������� ������� ���� ���������� ��� ��������� ���������� ������ ��������.
		�� ������� ��������� ������������ ������� ����� ����� ����� ���������. ����� � ������� ������������ � ���� ��� �������. 
		����� ���� ��� � ����� �������� ��� ����� ��������, �� ����� ������������ � �������� ���������, 
		������� ���� ���� ���������� � ���������� ����������� ����� ����� ���������.*/
		

		void fStack(int vG, int eG, int **mG, int *Res)
		{
			/*������ �������� - ������ ������ ��������*/
				int *xG = new int[eG];
				for (int i = 0; i < eG; i++)
					xG[i] = i;
			/*---*/

			/*�������� ���������� ������ �������� - 1 �����*/
			
				for (int j = 0; j < vG; j++)
					cout << xG[j] + 1 << " ";
				cout << "\n";
			
			/*---*/

			/*������������ ����� ������ �������� �� ������� ��������� ��������� �� � ���� - 1 �����*/
				int SRes = 0;
				for (int xi = 0; xi < vG - 1; xi++)
					for (int xj = xi + 1; xj < vG; xj++)
						SRes += mG[xG[xi]][xG[xj]];
				StackCreate(xG, vG, SRes);
			/*---*/

			/*����������� ���������� ������ ��������*/
				bool ret = true;
				while (ret == true)
				{
					for (int i = vG - 1; i >= 0; --i)
						if (xG[i] < eG - vG + i)
						{
							++xG[i];
							for (int j = i + 1; j < vG; ++j)
								xG[j] = xG[j - 1] + 1;

							/*������������ ����� ������ �������� �� ������� ��������� ��������� �� � ���� - 2 �����*/
								int SRes = 0;
								for (int xi = 0; xi < vG - 1; xi++)
									for (int xj = xi + 1; xj < vG; xj++)
										SRes += mG[xG[xi]][xG[xj]];
								StackAdd(xG, vG, SRes);
							/*---*/

							/*�������� ���������� ������ �������� - 2 �����*/
							
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

			/*���� ������� ��������� � ������� ����� ������ ���������������, �� �������� �������� ��������������� �� �������. ������� �������.*/
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





/*������� � �������� ��� ���*/
	struct Queue
	{
		/*����� ����� ������ ��������*/
		int SRes;
		/*---*/
		/*������ ������ ��������*/
		int *xG;
		/*---*/
		/*������ �� ��������� ������� �������*/
			Queue *next;
		/*---*/
	} *queueBOTTOM; //������ ������� �������

	/*�������� ��������*/
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

	/*���������� ��������*/
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

	/*�������� ��������*/
		void QueueDelete()
		{
			Queue *temp = new Queue;
			temp = queueBOTTOM->next;
			queueBOTTOM = NULL;
			queueBOTTOM = temp;
		};
	/*---*/

	/*������� �������*/

		/*�� ���� ����������������� �������� ���������� ������� ���� ���������� ��� ��������� ���������� ������ ��������. 
		�� ������� ��������� ������������ ������� ����� ����� ����� ���������. ����� � ������� ������������ � ������� ��� �������.
		����� ���� ��� � ������� �������� ��� ����� ��������, �� ����� ������������ � �������� ���������,
		������� ���� ���� ���������� (������� �������) � ���������� ����������� ����� ����� ���������.*/


		void fQueue(int vG, int eG, int **mG, int *Res)
		{
			/*������ �������� - ������ ������ ��������*/
				int *xG = new int[eG];
				for (int i = 0; i < eG; i++)
					xG[i] = i;
			/*---*/

			/*�������� ���������� ������ �������� - 1 �����*/
			
				for (int j = 0; j < vG; j++)
					cout << xG[j] + 1 << " ";
				cout << "\n";
			
			/*---*/

			/*������������ ����� ������ �������� �� ������� ��������� ��������� �� � ������� - 1 �����*/
				int SRes = 0;
				for (int xi = 0; xi < vG - 1; xi++)
					for (int xj = xi + 1; xj < vG; xj++)
						SRes += mG[xG[xi]][xG[xj]];
				QueueCreate(xG, vG, SRes);
			/*---*/

			/*����������� ���������� ������ ��������*/
				bool ret = true;
				while (ret == true)
				{
					for (int i = vG - 1; i >= 0; --i)
						if (xG[i] < eG - vG + i)
						{
							++xG[i];
							for (int j = i + 1; j < vG; ++j)
								xG[j] = xG[j - 1] + 1;

							/*������������ ����� ������ �������� �� ������� ��������� ��������� �� � ������� - 2 �����*/
								int SRes = 0;
								for (int xi = 0; xi < vG - 1; xi++)
									for (int xj = xi + 1; xj < vG; xj++)
										SRes += mG[xG[xi]][xG[xj]];
								QueueAdd(xG, vG, SRes);
							/*---*/

							/*�������� ���������� ������ �������� - 2 �����*/
							
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

			/*���� ������� ��������� � ������� �������� ������� ������ ���������������, �� �������� �������� ��������������� �� �������. ������� ������ �������.*/
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
/*-���������������-�������-���������-------------------------------------------------------------------------------------*/





int main()
{
	/*��������� ����� ��� ������ � ��� ������*/
		ifstream input("input.txt");
		ofstream output("output.txt");
	/*---*/

	/*���������� ������ ��������, ���������� ������ �����, ������� ���������*/
		int vG;
		int eG;
		int **mG;
	/*---*/

	/*������ - ���������� ������ ��������, ���������� ������ �����, ���� ������ �����*/
		input >> vG;
		input >> eG;
		mG = new int*[eG];
		for (int i = 0; i < eG; i++)
			mG[i] = new int[eG];
		for (int i = 0; i < eG; i++)
			for (int j = 0; j < eG; j++)
				input >> mG[i][j];
	/*---*/

	/*���� ������ ������*/
		int choose;
		cout << "Choose method:\n";
		cout << "1. Recursion.\n";
		cout << "2. Stack.\n";
		cout << "3. Queue.\n";
		cin >> choose;
	/*---*/

	/*�������� ���������� ������*/
		/*��������*/
			if (choose == 1)
			{
				/*�������������� ���������, ������ �������� - ������� ������ ��������*/
					int *Res = new int[vG];
					int *xG = new int[vG];
				/*---*/
				/*�������� �����*/
					unsigned int time = clock();
				/*---*/
					/*����� ������� �������� � �������� ������ � ���������*/
						fRecursion(xG, vG, eG, mG, Res); 
					/*---*/
				/*������� ������� ������ ��������� � �����*/
					cout << (clock() - time) / 1000.0 << " sec.\n";
				/*---*/
				/*����� ����������*/
					for (int i = 0; i < vG; i++)
						output << Res[i] << " ";
					output << "(" << TRes << ")";
				/*---*/
			}
		/*---*/
		/*����*/
			else if (choose == 2)
			{
				/*��������� - ������ ������ ��������*/
				int *Res = new int[vG];
				/*---*/
				/*�������� �����*/
					unsigned int time = clock();
				/*---*/
					/*����� ������� ����� � �������� ������ � ���������*/
						fStack(vG, eG, mG, Res);
					/*---*/
				/*������� ������� ������ ��������� � �����*/
					cout << (clock() - time) / 1000.0 << " sec.\n";
				/*---*/
				/*����� ����������*/
					for (int i = 0; i < vG; i++)
						output << Res[i] << " ";
					output << "(" << TRes << ")";
				/*---*/
			}
		/*---*/
		/*�������*/
			else if (choose == 3)
			{
				/*��������� - ������ ������ ��������*/
				int *Res = new int[vG];
				/*---*/
				/*�������� �����*/
					unsigned int time = clock();
				/*---*/
					/*����� ������� ������� � �������� ������ � ���������*/
						fQueue(vG, eG, mG, Res);
					/*---*/
				/*������� ������� ������ ��������� � �����*/
					cout << (clock() - time) / 1000.0 << " sec.\n";
				/*---*/
				/*����� ����������*/
					for (int i = 0; i < vG; i++)
						output << Res[i] << " ";
					output << "(" << TRes << ")";
				/*---*/
			};
		/*---*/
	/*---*/

	/*��������� ���� ��� ������ � ��� ������*/
		input.close();
		output.close();
	/*---*/

	/*����� � �������*/
		system("pause");
	/*---*/
};