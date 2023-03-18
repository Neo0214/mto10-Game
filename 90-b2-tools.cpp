#include <iostream>
#include <iomanip>
#include <conio.h>
#include "90-b2.h"
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
  �������ƣ�getcrt
  ��    �ܣ������������Ŀ��ֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void getcrt(int* row, int* col, int* target, char menu)
{
	while (1)
	{
		cout << "����������(5-8)��" << endl;
		cin >> *row;
		if (cin.good() && *row >= 5 && *row <= 8)
			break;
		else if (!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
	while (1)
	{
		cout << "����������(5-10)��" << endl;
		cin >> *col;
		if (cin.good() && *col >= 5 && *col <= 10)
			break;
		else if (!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
	if (menu == '3' || menu=='4' || menu == '9')
	{
		while (1)
		{
			cout << "������ϳ�Ŀ��(5-20)��" << endl;
			cin >> *target;
			if (cin.good() && *target >= 5 && *target <= 20)
				break;
			else if (!cin.good())
			{
				cin.clear();
				cin.ignore(1024, '\n');
			}
		}
	}
}

/***************************************************************************
  �������ƣ�init
  ��    �ܣ���ʼ�������ڲ�ֵ/��������
  ���������
  �� �� ֵ��
  ˵    �����������ڷ���ֵ�Ĳ���row1-8��col1-10
***************************************************************************/
void init(int a[10][12], int row, int col)
{
	int max = 0, i, j, n = 0;
	srand(unsigned (time(0)));
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
			max = max > a[i][j] ? max : a[i][j];
	}
	//�ҵ������岿�������ֵ
	if (max <= 3)
	{//Ӧ�ȸ�������
		for (i = 1; i <= row; i++)
		{
			for (j = 1; j <= col; j++)
			{
				if (a[i][j] == 0)//�ҵ�Ӧ���������ֵ�λ��
					a[i][j] = 1 + rand() % 3;
			}
		}
	}
	else if (max==4 || max==5)
	{
		for (i = 1; i <= row; i++)
		{
			for (j = 1; j <= col; j++)
			{
				if (a[i][j] == 0)//�ҵ�Ӧ���������ֵ�λ��
				{
					n = 1 + rand() % 100;
					if (n <= 150 - max * 15)//Ӧ������1-3
						a[i][j] = 1 + rand() % 3;
					else if (n > 90 && max == 5)
						a[i][j] = 5;
					else
						a[i][j] = 4;
				}
			}
		}
	}
	else if (max == 6)
	{
		for (i = 1; i <= row; i++)
		{
			for (j = 1; j <= col; j++)
			{
				if (a[i][j] == 0)
				{
					n = 1 + rand() % 100;
					if (n <= 80)
						a[i][j] = 1 + rand() % 4;
					else if (n > 95)
						a[i][j] = 6;
					else
						a[i][j] = 5;
				}
			}
		}
	}
	else
	{
		for (i = 1; i <= row; i++)
		{
			for (j = 1; j <= col; j++)
			{
				if (a[i][j] == 0)
				{
					n = 1 + rand() % 100;
					if (n <= 80 / (max - 3) * (max - 3))
						a[i][j] = 1 + rand() % (max - 3);
					else if (n <= 90)
						a[i][j] = max - 2;
					else if (n <= 95)
						a[i][j] = max - 1;
					else
						a[i][j] = max;
				}
			}
		}
	}
}









/***************************************************************************
  �������ƣ�findmerge
  ��    �ܣ��ҵ�������ĺϲ����
  ���������
  �� �� ֵ��1˵�����Ժϲ���0�޿ɺϲ���
  ˵    �����ǵݹ�
***************************************************************************/
int findmerge(int a[10][12], char getrow, char getcol, int row, int col, int merge[10][12])
{
	int i = getrow - 'A' + 1, j = getcol - '0' + 1, x, y;
	bool k = true;
	merge[i][j] = 1;
	while (k)
	{
		k = false;
		for (x = 1; x <= row; x++)
		{
			for (y = 1; y <= col; y++)
			{
				if (merge[x][y] == 1)//�˴�����������Ѱ��
				{
					if (a[x][y] == a[x - 1][y] && merge[x - 1][y] != 1)
					{
						merge[x - 1][y] = 1;
						k = true;
					}
					if (a[x][y] == a[x + 1][y] && merge[x + 1][y] != 1)
					{
						merge[x + 1][y] = 1;
						k = true;
					}
					if (a[x][y] == a[x][y - 1] && merge[x][y - 1] != 1)
					{
						merge[x][y - 1] = 1;
						k = true;
					}
					if (a[x][y] == a[x][y + 1] && merge[x][y + 1] != 1)
					{
						merge[x][y + 1] = 1;
						k = true;
					}
				}
			}
		}
	}
	if (merge[i + 1][j] == 1 || merge[i - 1][j] == 1 || merge[i][j - 1] == 1 || merge[i][j + 1] == 1)
		return 1;
	else
	{
		merge[i][j] = 0;
		return 0;
	}
}






/***************************************************************************
  �������ƣ�end
  ��    �ܣ�С�����������ʾ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void end()
{
	char in[50] = { '\0' };
	int i;
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	while (1)
	{
		for (i = 0; i < 50; i++)
			in[i] = '\0';
		cout << "��С�������������End����...";
		cin >> in;
		cin.ignore(1024, '\n');
		if (in[3] != '\0')
		{
			cout << "\n�����������������" << endl;
			continue;
		}
		in[0] = (in[0] >= 'a' && in[0] <= 'z') ? in[0] - 'a' + 'A' : in[0];
		in[1] = (in[1] >= 'a' && in[1] <= 'z') ? in[1] - 'a' + 'A' : in[1];
		in[2] = (in[2] >= 'a' && in[2] <= 'z') ? in[2] - 'a' + 'A' : in[2];
		if (in[3] == '\0' && in[0]=='E' && in[1]=='N' && in[2]=='D')
			break;
		else
			cout << "\n�����������������" << endl;
	}
}






/***************************************************************************
  �������ƣ�calc
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void calc(int a[10][12], int merge[10][12], int getrow, int getcol)
{
	int i, j;
	a[getrow - 'A' + 1][getcol - '0' + 1]++;
	for (i = 1; a[i][1] != 0; i++)
	{
		for (j = 1; a[i][j] != 0; j++)
		{
			if (merge[i][j] == 1 && !(i==getrow-'A'+1 && j==getcol-'0'+1))
				a[i][j] = 0;
		}
	}
}

/***************************************************************************
  �������ƣ�score
  ��    �ܣ����ر��κϳ�����õĵ÷�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int score(int a[10][12], int merge[10][12], int row, int col, char getrow, char getcol)
{
	int i, j, sum = 0, value = a[getrow - 'A' + 1][getcol - '0' + 1];
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (merge[i][j] == 1)
				sum++;
		}
	}
	return sum = sum * value * 3;
}








/***************************************************************************
  �������ƣ�mergeclear
  ��    �ܣ�����merge��������ͬ������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mergeclear(int merge[10][12])
{
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 12; j++)
		{
			merge[i][j] = 0;
		}
	}
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int win(int a[10][12], int target)
{
	int i, j, max = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (max < a[i][j])
				max = a[i][j];
		}
	}
	if (max == target)
		return 1;
	else
		return 0;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int lose(int a[10][12], int row, int col)
{
	int i, j;
	int merge[10][12] = { 0 };
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			mergeclear(merge);
			if (findmerge(a, i - 1 + 'A', j - 1 + '0', row, col, merge))
				return 0;
		}
	}
	return 1;
}
