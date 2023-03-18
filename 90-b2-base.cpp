#include <iostream>
#include <iomanip>
#include <conio.h>
#include "90-b2.h"
#include "cmd_console_tools.h"

using namespace std;

/***************************************************************************
  函数名称：baseprint
  功    能：打印初始数组状态
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void baseprint(int a[10][12], int row, int col)
{
	int i, j;
	cout << "\n当前数组：\n  |";
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
  函数名称：readln
  功    能：获得输入的坐标
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void readln(char* getrow, char* getcol, int row, int col)
{
	char in[31] = { '\0' };
	int i, j = 0;
	while (1)
	{
		cout << "\n请以字母+数字形式[例：c2]输入矩阵坐标：";
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
		cout << "输入错误，请重新输入.\n" << endl;
	}

}
/***************************************************************************
  函数名称：notice
  功    能：输出提示
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void notice(int k, char getrow, char getcol)
{
	cout << "输入为" << getrow << "行" << getcol - '0' << "列" << endl;
	if (k)
		cout << "\n查找结果数组：" << endl;
	else
		cout << "输入的矩阵坐标位置处无连续相同值，请重新输入";
}

/***************************************************************************
  函数名称：findout
  功    能：打印*查找结果
  输入参数：
  返 回 值：
  说    明：
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
  函数名称：findoutnow
  功    能：打印当前数组查找结果
  输入参数：
  返 回 值：
  说    明：
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
  函数名称：findmerge_rec
  功    能：找到该坐标合并情况
  输入参数：
  返 回 值：
  说    明：递归方式实现
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
  函数名称：ask
  功    能：询问是否确认合并
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char ask(char getrow, char getcol)
{
	char get = '\0';
	while (1)
	{
		cout << "请确认是否把相邻的相同值合并到" << getrow << getcol << "中(Y/N/Q)：";
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
  函数名称：fall
  功    能：使数字跳过0下落，挪动了数组a
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void fall(int a[10][12], int row, int col)
{
	int i, j, k;
	for (j = 1; j <= col; j++)//按列遍历
	{
		for (i = row; i >= 1; i--)//从下往上找
		{
			if (a[i][j] == 0)//找到一个0
			{
				for (k = i; k >= 1; k--)//从此位置往上找
				{
					if (a[k][j] != 0)//找到不为0的数
					{
						a[i][j] = a[k][j];//将其落下
						a[k][j] = 0;//落下后原位置为0
						break;
					}
				}
			}
		}
	}
}

/***************************************************************************
  函数名称：enter
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void enter(int judge)
{
	char ch = '\0';
	if (judge == 1)
		cout << "按回车键进行数组下落除0操作...";
	else if (judge == 2)
		cout << "按回车键进行新值填充...";
	else
		cout << "本次合成结束，按回车键继续新一次的合成" << endl;
	while (1)
	{
		ch = _getch();
		if (ch == '\r')
			break;
	}
	cout << endl;
}

/***************************************************************************
  函数名称：findoutfall
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void findoutfall(int a[10][12], int merge[10][12], int row, int col)
{
	int i, j;
	cout << "除0后的数组(不同色标识):" << endl;
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
	int a[10][12] = { 0 }, k = 0;//初始化全部为0，最大8x10的外圈也全部为0
	int merge[10][12] = { 0 };//将要合并的坐标会变为1，和a数组保持一致坐标，方便统一处理
	char getrow=0, getcol=0;//输入合并坐标
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
	cout << "\n\n当前数组(不同色标识)：" << endl;
	findoutnow(a, merge, row, col);
	cout << endl;
	end();
	return;
}

void menu2(int row, int col)
{
	int a[10][12] = { 0 }, k = 0, i, j;//初始化全部为0，最大8x10的外圈也全部为0
	int merge[10][12] = { 0 };//将要合并的坐标会变为1，和a数组保持一致坐标，方便统一处理
	char getrow = 0, getcol = 0;//输入合并坐标
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
	cout << "\n\n当前数组(不同色标识)：" << endl;
	findoutnow(a, merge, row, col);
	end();
	return;
}

void menu3(int row, int col, int target)
{
	int a[10][12] = { 0 }, k = 0;//初始化全部为0，最大8x10的外圈也全部为0
	int merge[10][12] = { 0 };//将要合并的坐标会变为1，和a数组保持一致坐标，方便统一处理
	int thistime = 0, sum = 0;
	char getrow = 0, getcol = 0, choice;//输入合并坐标
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
		cout << "\n\n当前数组(不同色标识)：" << endl;
		findoutnow(a, merge, row, col);
		choice = ask(getrow, getcol);
		if (choice == 'Y')
		{
			calc(a, merge, getrow, getcol);
			cout << "\n相同值归并后的数组(不同色标识)：" << endl;
			findoutnow(a, merge, row, col);
			thistime = score(a, merge, row, col, getrow, getcol);
			sum += thistime;
			cout << "本次得分：" << thistime << " 总得分：" << sum << " 合成目标：" << target << endl << endl;
			enter(1);
			fall(a, row, col);//对数组a进行下落处理
			mergeclear(merge);
			findoutfall(a, merge, row, col);
			enter(2);
			cout << "新值填充后的数组(不同色标识)：" << endl;
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
	int a[10][12] = { 0 }, k = 0;//初始化全部为0，最大8x10的外圈也全部为0
	int merge[10][12] = { 0 };//将要合并的坐标会变为1，和a数组保持一致坐标，方便统一处理
	int thistime = 0, sum = 0;
	char getrow = 0, getcol = 0, choice;//输入合并坐标
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
		cout << "\n\n当前数组(不同色标识)：" << endl;
		findoutnow(a, merge, row, col);
		choice = ask(getrow, getcol);
		if (choice == 'Y')
		{
			calc(a, merge, getrow, getcol);
			cout << "\n相同值归并后的数组(不同色标识)：" << endl;
			findoutnow(a, merge, row, col);
			thistime = score(a, merge, row, col, getrow, getcol);
			sum += thistime;
			cout << "本次得分：" << thistime << " 总得分：" << sum << " 合成目标：" << target << endl << endl;
			enter(1);
			fall(a, row, col);//对数组a进行下落处理
			mergeclear(merge);
			findoutfall(a, merge, row, col);
			enter(2);
			cout << "新值填充后的数组(不同色标识)：" << endl;
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
			cout << "已经合成到" << target;
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cout << endl;
			cout << "按回车键继续向更高目标进发" << endl;
			while (_getch() != '\r')
				;
			target++;
		}
		if (lose(a, row, col))
		{
			cout << "\n无可合并的项，游戏结束！                ";
			break;
		}
		
		mergeclear(merge);

	}
	end();
}