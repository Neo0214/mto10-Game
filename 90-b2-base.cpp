#include <iostream>
#include <iomanip>
#include <conio.h>
#include "90-b2.h"
#include "cmd_console_tools.h"

using namespace std;

/***************************************************************************
  �������ƣ�baseprint
  ��    �ܣ���ӡ��ʼ����״̬
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void baseprint(int a[10][12], int row, int col)
{
	int i, j;
	cout << "\n��ǰ���飺\n  |";
	for (i = 0; i < col; i++)
		cout << setw(3) << i;
	cout << endl;
	for (i = 0; i <= col; i++)
	{
		if (i == 0)
			cout << "--+";
		else
			cout << "---";
	}
	cout << "-" << endl;
	for (i = 0; i < row; i++)
	{
		cout << char('A' + i) << setw(2) << "|";
		for (j = 0; j < col; j++)
		{
			cout << setw(3) << a[i + 1][j + 1];
		}
		cout << endl;
	}
}

/***************************************************************************
  �������ƣ�readln
  ��    �ܣ�������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void readln(char* getrow, char* getcol, int row, int col)
{
	char in[31] = { '\0' };
	int i, j = 0;
	while (1)
	{
		cout << "\n������ĸ+������ʽ[����c2]����������꣺";
		for (i = 0; i < 31; i++)
			in[i] = '\0';
		for (i = 0; i < 30; i++)
		{
			in[i] = _getch();
			if (in[i] >= 32 && in[i] <= 126)
				cout << in[i];
			else if (in[i] == '\r')
			{
				cout << endl;
				break;
			}
			else
				i--;
		}
		if (in[2] == '\r')
		{
			in[0] = (in[0] >= 'a' && in[0] <= 'z') ? in[0] - 'a' + 'A' : in[0];
			in[1] = (in[1] >= 'a' && in[1] <= 'z') ? in[1] - 'a' + 'A' : in[1];
			if ((in[0] >= 'A' && in[0] <= 'A' + row) && (in[1] >= '0' && in[1] <= '0' + col))
			{
				*getrow = in[0];
				*getcol = in[1];
				break;
			}
		}
		cout << "�����������������.\n" << endl;
	}

}
/***************************************************************************
  �������ƣ�notice
  ��    �ܣ������ʾ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void notice(int k, char getrow, char getcol)
{
	cout << "����Ϊ" << getrow << "��" << getcol - '0' << "��" << endl;
	if (k)
		cout << "\n���ҽ�����飺" << endl;
	else
		cout << "����ľ�������λ�ô���������ֵͬ������������";
}

/***************************************************************************
  �������ƣ�findout
  ��    �ܣ���ӡ*���ҽ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void findout(int merge[10][12], int row, int col)
{
	int i, j;
	cout << "  |";
	for (i = 0; i < col; i++)
		cout << setw(3) << i;
	cout << endl;
	for (i = 0; i <= col; i++)
	{
		if (i == 0)
			cout << "--+";
		else
			cout << "---";
	}
	cout << "-" << endl;
	for (i = 0; i < row; i++)
	{
		cout << char('A' + i) << setw(2) << "|";
		for (j = 0; j < col; j++)
		{
			if (merge[i + 1][j + 1] == 0)
				cout << setw(3) << merge[i + 1][j + 1];
			else
				cout << setw(3) << "*";
		}
		cout << endl;
	}
}

/***************************************************************************
  �������ƣ�findoutnow
  ��    �ܣ���ӡ��ǰ������ҽ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void findoutnow(int a[10][12], int merge[10][12], int row, int col)
{
	int i, j;
	cout << "  |";
	for (i = 0; i < col; i++)
		cout << setw(3) << i;
	cout << endl;
	for (i = 0; i <= col; i++)
	{
		if (i == 0)
			cout << "--+";
		else
			cout << "---";
	}
	cout << "-" << endl;
	for (i = 1; i <= row; i++)
	{
		cout << char('A' + i - 1) << " |";
		for (j = 1; j <= col; j++)
		{
			if (merge[i][j] == 1)
			{
				cout << "  ";
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
				cout << a[i][j];
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			}
			else
				cout << setw(3) << a[i][j];
		}
		cout << endl;
	}
}

/***************************************************************************
  �������ƣ�findmerge_rec
  ��    �ܣ��ҵ�������ϲ����
  ���������
  �� �� ֵ��
  ˵    �����ݹ鷽ʽʵ��
***************************************************************************/
void findmerge_rec(int a[10][12], char getrow, char getcol, int row, int col, int merge[10][12])
{
	int i = getrow - 'A' + 1, j = getcol - '0' + 1;
	merge[i][j] = 1;
	if (a[i][j] == a[i - 1][j] && merge[i - 1][j] != 1)
		findmerge_rec(a, getrow - 1, getcol, row, col, merge);
	if (a[i][j] == a[i + 1][j] && merge[i + 1][j] != 1)
		findmerge_rec(a, getrow + 1, getcol, row, col, merge);
	if (a[i][j] == a[i][j - 1] && merge[i][j - 1] != 1)
		findmerge_rec(a, getrow, getcol - 1, row, col, merge);
	if (a[i][j] == a[i][j + 1] && merge[i][j + 1] != 1)
		findmerge_rec(a, getrow, getcol + 1, row, col, merge);
	return;

}

/***************************************************************************
  �������ƣ�ask
  ��    �ܣ�ѯ���Ƿ�ȷ�Ϻϲ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
char ask(char getrow, char getcol)
{
	char get = '\0';
	while (1)
	{
		cout << "��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���" << getrow << getcol << "��(Y/N/Q)��";
		get = _getch();
		if (get == 'Y' || get == 'N' || get == 'Q' || get == 'y' || get == 'n' || get == 'q')
		{
			cout << get << endl;
			get = (get >= 'a' && get <= 'z') ? get - 'a' + 'A' : get;
			break;
		}
		cout << endl;
	}
	return get;
}

/***************************************************************************
  �������ƣ�fall
  ��    �ܣ�ʹ��������0���䣬Ų��������a
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void fall(int a[10][12], int row, int col)
{
	int i, j, k;
	for (j = 1; j <= col; j++)//���б���
	{
		for (i = row; i >= 1; i--)//����������
		{
			if (a[i][j] == 0)//�ҵ�һ��0
			{
				for (k = i; k >= 1; k--)//�Ӵ�λ��������
				{
					if (a[k][j] != 0)//�ҵ���Ϊ0����
					{
						a[i][j] = a[k][j];//��������
						a[k][j] = 0;//���º�ԭλ��Ϊ0
						break;
					}
				}
			}
		}
	}
}

/***************************************************************************
  �������ƣ�enter
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void enter(int judge)
{
	char ch = '\0';
	if (judge == 1)
		cout << "���س����������������0����...";
	else if (judge == 2)
		cout << "���س���������ֵ���...";
	else
		cout << "���κϳɽ��������س���������һ�εĺϳ�" << endl;
	while (1)
	{
		ch = _getch();
		if (ch == '\r')
			break;
	}
	cout << endl;
}

/***************************************************************************
  �������ƣ�findoutfall
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void findoutfall(int a[10][12], int merge[10][12], int row, int col)
{
	int i, j;
	cout << "��0�������(��ͬɫ��ʶ):" << endl;
	cout << "  |";
	for (i = 0; i < col; i++)
		cout << setw(3) << i;
	cout << endl;
	for (i = 0; i <= col; i++)
	{
		if (i == 0)
			cout << "--+";
		else
			cout << "---";
	}
	cout << "-" << endl;
	for (i = 1; i <= row; i++)
	{
		cout << char('A' + i - 1) << " |";
		for (j = 1; j <= col; j++)
		{
			if (a[i][j] == 0)
			{
				merge[i][j] = 1;
				cout << "  ";
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
				cout << a[i][j];
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			}
			else
				cout << setw(3) << a[i][j];
		}
		cout << endl;
	}
}


void menu1(int row, int col)
{
	int a[10][12] = { 0 }, k = 0;//��ʼ��ȫ��Ϊ0�����8x10����ȦҲȫ��Ϊ0
	int merge[10][12] = { 0 };//��Ҫ�ϲ���������Ϊ1����a���鱣��һ�����꣬����ͳһ����
	char getrow=0, getcol=0;//����ϲ�����
	init(a, row, col);
	baseprint(a, row, col);
	while (!k)
	{
		mergeclear(merge);
		readln(&getrow, &getcol, row, col);
		k = findmerge(a, getrow, getcol, row, col, merge);
		notice(k, getrow, getcol);
	}
	findout(merge, row, col);
	cout << "\n\n��ǰ����(��ͬɫ��ʶ)��" << endl;
	findoutnow(a, merge, row, col);
	cout << endl;
	end();
	return;
}

void menu2(int row, int col)
{
	int a[10][12] = { 0 }, k = 0, i, j;//��ʼ��ȫ��Ϊ0�����8x10����ȦҲȫ��Ϊ0
	int merge[10][12] = { 0 };//��Ҫ�ϲ���������Ϊ1����a���鱣��һ�����꣬����ͳһ����
	char getrow = 0, getcol = 0;//����ϲ�����
	init(a, row, col);
	baseprint(a, row, col);
	while (!k)
	{
		k = 0;
		mergeclear(merge);
		readln(&getrow, &getcol, row, col);
		findmerge_rec(a, getrow, getcol, row, col, merge);
		for (i = 1; i <= row; i++)
		{
			for (j = 1; j <= col; j++)
			{
				if (merge[i][j] == 1)
				{
					k += 1;
				}
			}
		}
		k = k > 1 ? 1 : 0;
		notice(k, getrow, getcol);
	}
	findout(merge, row, col);
	cout << "\n\n��ǰ����(��ͬɫ��ʶ)��" << endl;
	findoutnow(a, merge, row, col);
	end();
	return;
}

void menu3(int row, int col, int target)
{
	int a[10][12] = { 0 }, k = 0;//��ʼ��ȫ��Ϊ0�����8x10����ȦҲȫ��Ϊ0
	int merge[10][12] = { 0 };//��Ҫ�ϲ���������Ϊ1����a���鱣��һ�����꣬����ͳһ����
	int thistime = 0, sum = 0;
	char getrow = 0, getcol = 0, choice;//����ϲ�����
	init(a, row, col);
	baseprint(a, row, col);
	while (1)
	{
		mergeclear(merge);
		k = false;
		while (!k)
		{
			readln(&getrow, &getcol, row, col);
			k = findmerge(a, getrow, getcol, row, col, merge);
			notice(k, getrow, getcol);
		}
		findout(merge, row, col);
		cout << "\n\n��ǰ����(��ͬɫ��ʶ)��" << endl;
		findoutnow(a, merge, row, col);
		choice = ask(getrow, getcol);
		if (choice == 'Y')
		{
			calc(a, merge, getrow, getcol);
			cout << "\n��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
			findoutnow(a, merge, row, col);
			thistime = score(a, merge, row, col, getrow, getcol);
			sum += thistime;
			cout << "���ε÷֣�" << thistime << " �ܵ÷֣�" << sum << " �ϳ�Ŀ�꣺" << target << endl << endl;
			enter(1);
			fall(a, row, col);//������a�������䴦��
			mergeclear(merge);
			findoutfall(a, merge, row, col);
			enter(2);
			cout << "��ֵ���������(��ͬɫ��ʶ)��" << endl;
			init(a, row, col);
			findoutnow(a, merge, row, col);
			break;
		}
		else if (choice == 'Q')
		{
			cout << endl;
			break;
		}
	}
	end();
}

void menu4(int row, int col, int target)
{
	int a[10][12] = { 0 }, k = 0;//��ʼ��ȫ��Ϊ0�����8x10����ȦҲȫ��Ϊ0
	int merge[10][12] = { 0 };//��Ҫ�ϲ���������Ϊ1����a���鱣��һ�����꣬����ͳһ����
	int thistime = 0, sum = 0;
	char getrow = 0, getcol = 0, choice;//����ϲ�����
	init(a, row, col);
	while (1)
	{
		baseprint(a, row, col);
		k = false;
		while (!k)
		{
			readln(&getrow, &getcol, row, col);
			k = findmerge(a, getrow, getcol, row, col, merge);
			notice(k, getrow, getcol);
		}
		findout(merge, row, col);
		cout << "\n\n��ǰ����(��ͬɫ��ʶ)��" << endl;
		findoutnow(a, merge, row, col);
		choice = ask(getrow, getcol);
		if (choice == 'Y')
		{
			calc(a, merge, getrow, getcol);
			cout << "\n��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
			findoutnow(a, merge, row, col);
			thistime = score(a, merge, row, col, getrow, getcol);
			sum += thistime;
			cout << "���ε÷֣�" << thistime << " �ܵ÷֣�" << sum << " �ϳ�Ŀ�꣺" << target << endl << endl;
			enter(1);
			fall(a, row, col);//������a�������䴦��
			mergeclear(merge);
			findoutfall(a, merge, row, col);
			enter(2);
			cout << "��ֵ���������(��ͬɫ��ʶ)��" << endl;
			init(a, row, col);
			findoutnow(a, merge, row, col);
			enter(3);
		}
		else if (choice == 'Q')
		{
			cout << endl;
			break;
		}

		if (win(a, target))
		{
			cct_setcolor(COLOR_HWHITE, COLOR_RED);
			cout << "�Ѿ��ϳɵ�" << target;
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cout << endl;
			cout << "���س������������Ŀ�����" << endl;
			while (_getch() != '\r')
				;
			target++;
		}
		if (lose(a, row, col))
		{
			cout << "\n�޿ɺϲ������Ϸ������                ";
			break;
		}
		
		mergeclear(merge);

	}
	end();
}