#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include "90-b2.h"
#include "cmd_console_tools.h"
using namespace std;
/***************************************************************************
  函数名称：draw
  功    能：打印无边框图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void draw(int a[10][12], int row, int col)
{
	int i, j;
	cout << "当前屏幕设置为：" << 5 * row + 2 << "行" << 8 * (col + 1) << "列                  " << endl;
	cout << "      " << 0;
	for (j = 1; j < col; j++)
		cout << setw(6) << j;//打完第一行数字
	cout << "\n  ";
	for (j = 0; j < col * 3 + 2; j++)
	{
		cct_setcolor(15, 0);
		if (j == 0)
			cout << "┏";
		else if (j == col * 3 + 1)
			cout << "┓";
		else
			cout << "━";
	}//打印首行
	cout << endl;
	Sleep(2);
	for (i = 1; i < (row * 3 + 2); i++)//一共的行数，除去首位行
	{
		cct_setcolor(0, 7);
		if (i == 1)
			continue;
		if (i % 3 == 0)
			cout << char('A' + i / 3 - 1) << " ";
		else
			cout << "  ";
		//
		for (j = 0; j < col * 3 + 2; j++)
		{
			cct_setcolor(15, 0);
			if (j == 0 || j == col * 3 + 1)
				cout << "┃";
			else
				cout << "  ";
			Sleep(1);
		}
		cout << endl;
		cct_setcolor(0, 7);
		Sleep(2);
	}
	cout << "  ";
	for (j = 0; j < col * 3 + 2; j++)//打印尾行
	{
		cct_setcolor(15, 0);
		if (j == 0)
			cout << "┗";
		else if (j == col * 3 + 1)
			cout << "┛";
		else
			cout << "━";
	}
	cout << endl;
	for (i = 0; i < row * 3; i++)
	{
		Sleep(2);
		cct_gotoxy(4, 3 + i);
		for (j = 0; j < col; j++)
		{
			cct_setcolor(a[i/3+1][j+1], 0);
			if (i % 3 == 0)//首行
				cout << "┏" << "━" << "┓";
			else if ((i - 1) % 3 == 0)
				cout << "┃" << a[i/3+1][j+1] << " " << "┃";
			else
				cout << "┗" << "━" << "┛";
		}
	}
	cout << "\n\n";
	cct_setcolor(0, 7);
}

void menu5(int row, int col)
{
	cct_cls();
	int a[10][12] = { 0 }, k = 0;//初始化全部为0，最大8x10的外圈也全部为0
	int merge[10][12] = { 0 };//将要合并的坐标会变为1，和a数组保持一致坐标，方便统一处理
	char getrow = 0, getcol = 0;//输入合并坐标
	init(a, row, col);
	draw(a, row, col);
	end();
}
/***************************************************************************
  函数名称：draw6
  功    能：打印有边框图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void draw6(int a[10][12], int row, int col)
{
	int i, j;
	cout << "当前屏幕设置为：" << 5 * row + 2 << "行" << 8 * (col + 1) << "列" << endl;
	cout << "      0";
	for (i = 1; i < col; i++)
		cout << setw(8) << i;
	cout << "\n  ";
	for (j = 0; j < col * 4 + 1; j++)
	{
		cct_setcolor(15, 0);
		if (j == 0)
			cout << "┏";
		else if (j == col * 4)
			cout << "┓";
		else if (j % 4 == 0)
			cout << "┳";
		else
			cout << "━";
	}
	cout << endl;
	for (i = 1; i <= row * 4 - 1; i++)
	{
		cct_setcolor(0, 7);
		if ((i + 2) % 4 == 0)
			cout << char('A' + i / 4) << " ";
		else
			cout << "  ";
		for (j = 0; j <= 4 * col; j++)
		{
			Sleep(2);
			cct_setcolor(15, 0);
			if (j % 4 != 0 && i % 4 != 0)
				cout << "  ";
			else if (j % 4 == 0 && i % 4 != 0)
				cout << "┃";
			else if (j % 4 != 0 && i % 4 == 0)
				cout << "━";
			else if (j % 4 == 0 && i % 4 == 0 && j != 0 && j != 4 * col)
				cout << "╋";
			else if (j == 0 && i % 4 == 0)
				cout << "┣";
			else
				cout << "┫";
		}
		cout << endl;
		Sleep(2);
	}
	cct_setcolor(0, 7);
	cout << "  ";
	for (j = 0; j < col * 4 + 1; j++)
	{
		cct_setcolor(15, 0);
		if (j == 0)
			cout << "┗";
		else if (j == col * 4)
			cout << "┛";
		else if (j % 4 == 0)
			cout << "┻";
		else
			cout << "━";
	}
	//底板
	int basey = 3, basex = 4, x, y, n;
	for (i = 1; i <= row; i++)
	{
		Sleep(1);
		for (j = 1; j <= col; j++)//打印该元素元素块
		{
			Sleep(1);
			x = basex + 8 * (j - 1);
			y = basey + 4 * (i - 1);
			cct_setcolor(a[i][j], 0);
			for (n = 0; n < 3; n++)
			{
				cct_gotoxy(x, y + n);
				if (n == 0)
					cout << "┏━┓";
				else if (n == 1)
					cout << "┃" << a[i][j] << " ┃";
				else
					cout << "┗━┛";
			}
			
		}
	}



	cct_setcolor(0, 7);
	cout << "\n\n";
	
}

void menu6(int row, int col)
{
	cct_cls();
	int a[10][12] = { 0 }, k = 0;//初始化全部为0，最大8x10的外圈也全部为0
	int merge[10][12] = { 0 };//将要合并的坐标会变为1，和a数组保持一致坐标，方便统一处理
	init(a, row, col);
	draw6(a, row, col);
	end();
}
/***************************************************************************
  函数名称：light
  功    能：点亮或变黑某个指定坐标块
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void light(int a[10][12], int rownow, int colnow, int glow)
{
	int basey = 3, basex = 4, x, y, n;
	x = basex + 8 * (colnow - 1);
	y = basey + 4 * (rownow - 1);
	cct_setcolor(a[rownow][colnow], glow);
	for (n = 0; n < 3; n++)
	{
		cct_gotoxy(x, y + n);
		if (n == 0)
			cout << "┏━┓";
		else if (n == 1 && a[rownow][colnow] <= 9)
			cout << "┃" << a[rownow][colnow] << " ┃";
		else if (n == 1 && a[rownow][colnow] >= 10)
			cout << "┃" << a[rownow][colnow] << "┃";
		else
			cout << "┗━┛";
	}
	cct_setcolor(0, 7);
}
/***************************************************************************
  函数名称：judge_mouse
  功    能：根据鼠标位置和状态随时更新屏幕上的显示状态
  输入参数：
  返 回 值：1说明合法位置，0位置非法
  说    明：只断不读
***************************************************************************/
int judge_mouse(int a[10][12], int x, int y, int row, int col, int* rownow, int* colnow)
{
	int starow = *rownow, stacol = *colnow;//记录当前亮块位置
	x = x - 2;
	y = y - 2;//左上角第一个色块当成(0,0)
	if ((y % 4 != 0 && y <= row * 4 && y > 0) && (x % 8 != 0 && (x - 1) % 8 != 0 && x > 0 && x < col * 8))
	{
		*rownow = y / 4 + 1;
		*colnow = x / 8 + 1;//获取当前鼠标所在区域
		if (*rownow != starow || *colnow != stacol)//若鼠标区域发生变化
		{
			light(a, starow, stacol, COLOR_BLACK);
			light(a, *rownow, *colnow, COLOR_HWHITE);
			starow = *rownow;
			stacol = *colnow;
			cct_setcolor(0, 7);
			cct_gotoxy(0, row * 4 + 4);
			cout << "[当前鼠标] " << char('A' + *rownow - 1) << "行" << *colnow - 1 << "列                                          ";
		}
		else//若鼠标区域不发生变化
		{
			light(a, *rownow, *colnow, COLOR_HWHITE);
			cct_setcolor(0, 7);
			cct_gotoxy(0, row * 4 + 4);
			cout << "[当前鼠标] " << char('A' + *rownow - 1) << "行" << *colnow - 1 << "列                                         ";
		}
		return 1;
	}
	else
	{
		light(a, starow, stacol, COLOR_BLACK);
		cct_setcolor(0, 7);
		cct_gotoxy(0, row * 4 + 4);
		cout << "[当前鼠标] 位置非法                                                       ";
		return 0;
	}
	
}
/***************************************************************************
  函数名称：judge_key
  功    能：根据键盘状态随时更新屏幕上的显示状态
  输入参数：
  返 回 值：不存在非法位置，永远返回1
  说    明：只断不读
***************************************************************************/
int judge_key(int a[10][12], int keycode1, int keycode2, int row, int col, int* rownow, int* colnow)
{
	int starow = *rownow, stacol = *colnow;//记录当前亮块位置
	int k = 0;
	if (keycode1 == 224)
	{
		if (keycode2 == KB_ARROW_UP)
		{
			k = *rownow == 1 ? 0 : 1;
			*rownow = *rownow + row - 1 - k * row;
			light(a, starow, stacol, COLOR_BLACK);
			starow = *rownow;
			light(a, starow, stacol, COLOR_HWHITE);
		}
		else if (keycode2 == KB_ARROW_DOWN)
		{
			k = *rownow == row ? 0 : 1;
			*rownow = *rownow - row + 1 + k * row;
			light(a, starow, stacol, COLOR_BLACK);
			starow = *rownow;
			light(a, starow, stacol, COLOR_HWHITE);
		}
		else if (keycode2 == KB_ARROW_RIGHT)
		{
			k = *colnow == col ? 0 : 1;
			*colnow = *colnow - col + 1 + k * col;
			light(a, starow, stacol, COLOR_BLACK);
			stacol = *colnow;
			light(a, starow, stacol, COLOR_HWHITE);
		}
		else if (keycode2 == KB_ARROW_LEFT)
		{
			k = *colnow == 1 ? 0 : 1;
			*colnow = *colnow + col - 1 - k * col;
			light(a, starow, stacol, COLOR_BLACK);
			stacol = *colnow;
			light(a, starow, stacol, COLOR_HWHITE);
		}
	}
	cct_setcolor(0, 7);
	cct_gotoxy(0, row * 4 + 4);
	cout << "[当前键盘] " << char('A' + *rownow - 1) << "行" << *colnow-1 << "列                                   ";
	return 1;
}


void menu7(int row, int col)
{
	cct_cls();
	cct_setcursor(3);
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int rownow=1, colnow=1;
	int a[10][12] = { 0 };//初始化全部为0，最大8x10的外圈也全部为0
	int merge[10][12] = { 0 };//将要合并的坐标会变为1，和a数组保持一致坐标，方便统一处理
	init(a, row, col);
	draw6(a, row, col);//画出带框图形
	cct_enable_mouse();
	light(a, rownow, colnow, COLOR_HWHITE);//点亮左上角的块
	while (1)
	{
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT)//若使用鼠标
		{
			judge_mouse(a, X, Y, row, col, &rownow, &colnow);
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			judge_key(a, keycode1, keycode2, row, col, &rownow, &colnow);
		}

		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
		{
			cct_gotoxy(0, row * 4 + 4);
			cout << "选中了" << char('A' + rownow - 1) << "行" << colnow - 1 << "列          " << endl;
			break;
		}
		else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK)
		{
			cct_gotoxy(0, row * 4 + 4);
			cout << "选中了" << char('A' + rownow - 1) << "行" << colnow - 1 << "列          " << endl;
			break;
		}
		else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 13 && keycode2 == 0)
		{
			cct_gotoxy(0, row * 4 + 4);
			cout << "选中了" << char('A' + rownow - 1) << "行" << colnow - 1 << "列              " << endl;
			break;
		}
		else if (ret == CCT_KEYBOARD_EVENT && (keycode1 == 'q' || keycode1 == 'Q') && keycode2 == 0)
		{
			cct_gotoxy(0, row * 4 + 4);
			cout << "选中了" << char('A' + rownow - 1) << "行" << colnow - 1 << "列          " << endl;
			break;
		}
	}
	cct_setcursor(2);
	end();
}
/***************************************************************************
  函数名称：scan
  功    能：将第一次选中位置将要消去的块依次点亮
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void scan(int a[10][12], int merge[10][12], int row, int col, int bw, int rownow=0, int colnow=0)
{
	int i, j;
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (merge[i][j] == 1 && !(i==rownow && j==colnow))
			{
				light(a, i, j, bw);
				Sleep(1);
			}
		}
	}


}
/***************************************************************************
  函数名称：range
  功    能：判断鼠标是否在正确位置内且没有放到非亮块上
  输入参数：
  返 回 值：正确返回1，错误返回0
  说    明：
***************************************************************************/
int range(int x, int y, int rownow, int colnow, int row, int col)
{
	x = x - 2;
	y = y - 2;//左上角第一个色块当成(0,0)
	if ((y % 4 != 0 && y <= row * 4 && y > 0) && (x % 8 != 0 && (x - 1) % 8 != 0 && x > 0 && x < col * 8))
	{//在正确范围内
		if (rownow == y / 4 + 1 && colnow == x / 8 + 1)
			return 1;
	}
	return 0;
}
/***************************************************************************
  函数名称：various_choose
  功    能：不断读取键盘和鼠标状态，做出调用等具体步骤
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int various_choose(int a[10][12], int row, int col, int& rownow, int& colnow, int merge[10][12])
{
	int ret, maction;
	int keycode1, keycode2;
	int k = 0, judge = 0;
	int x = 0, y = 0, ev = 0;
	while (1)
	{
		mergeclear(merge);
		judge = 0;
		ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)//鼠标动了
		{
			k = judge_mouse(a, x, y, row, col, &rownow, &colnow);
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			k = judge_key(a, keycode1, keycode2, row, col, &rownow, &colnow);
		}
		//k=0什么也不做，k!=0再做

		ev = findmerge(a, rownow + 'A' - 1, colnow + '0' - 1, row, col, merge);//获取当前区域是否是可以合成的块
		if (k && ret==CCT_MOUSE_EVENT && maction==MOUSE_LEFT_BUTTON_CLICK)
		{
			if (ev)//当前块可以合成
			{
				cct_gotoxy(0, row * 4 + 4);
				cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
				judge = 1;
			}
			else//当前块不能合成
			{
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "周围无相同值                                    ";
				judge = 2;
			}
		}
		else if (k && ret == CCT_KEYBOARD_EVENT && keycode1 == '\r' && keycode2 == 0)
		{
			if (ev)
			{
				cct_gotoxy(0, row * 4 + 4);
				cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
				judge = 1;
			}
			else
			{
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "周围无相同值                                         ";
				judge = 2;
			}
		}
		if (judge == 1)//当前块可以合成时，点亮区域，等待二次确认
		{
			scan(a, merge, row, col, COLOR_WHITE, rownow, colnow);
			while (1)
			{
				ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)
				{
					if (!range(x, y, rownow, colnow, row, col))//位置变化
					{
						scan(a, merge, row, col, COLOR_BLACK);
						break;
					}
				}
				else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
				{
					return 1;
				}
				else if (ret == CCT_KEYBOARD_EVENT && keycode1 == '\r' && keycode2 == 0)
					return 1;
				else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 224 && (keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT || keycode2 == KB_ARROW_UP))
				{
					scan(a, merge, row, col, COLOR_BLACK);
					judge_key(a, keycode1, keycode2, row, col, &rownow, &colnow);
					break;
				}
			}
		}
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK)
			return 0;
		else if (ret == CCT_KEYBOARD_EVENT && (keycode1 == 'Q' || keycode1 == 'q') && keycode2 == 0)
			return 0;
		if (judge == 2)
		{
			while (1)
			{
				ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)
				{
					if (!range(x, y, rownow, colnow, row, col))
						break;
				}
				else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK)
					return 0;
				else if (ret == CCT_KEYBOARD_EVENT && (keycode1 == 'q' || keycode1 == 'Q') && keycode2 == 0)
					return 0;
				else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 224 && (keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT || keycode2 == KB_ARROW_UP))
				{
					judge_key(a, keycode1, keycode2, row, col, &rownow, &colnow);
					break;
				}
			}
		}
	}
}
/***************************************************************************
  函数名称：disappear
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void disappear(int a[10][12], int row, int col, int rownow, int colnow, int merge[10][12])
{
	int i, j, n;
	cct_setcolor(15, 15);
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (!(i == rownow && j == colnow) && merge[i][j] == 1)
			{
				for (n = 0; n < 3; n++)
				{
					cct_gotoxy(4 + (j - 1) * 8, 3 + 4 * (i - 1) + n);
					cout << "      ";
				}
			}
			else if (i == rownow && j == colnow)
			{
				a[i][j]++;
				cct_setcolor(a[i][j], 0);
				for (n = 0; n < 3; n++)
				{
					cct_gotoxy(4 + (j - 1) * 8, 3 + 4 * (i - 1) + n);
					if (n == 0)
						cout << "┏" << "━" << "┓";
					else if (n == 1 && a[i][j] <= 9)
						cout << "┃" << a[i][j] << " ┃";
					else if (n==1 && a[i][j]>=10)
						cout << "┃" << a[i][j] << "┃";
					else
						cout << "┗" << "━" << "┛";
				}
				cct_setcolor(15, 15);
			}
		}
	}
}

void twinkle(int a[10][12], int rownow, int colnow)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		Sleep(100);
		light(a, rownow, colnow, i % 2 * COLOR_HWHITE);
	}
}

void anime(int n, int i, int color, int colnow)
{//从第n行落到第i行，颜色为color
	int times, j;
	for (times = (i - n) * 4; times > 0; times--)//一共要来回打印消除这些次数
	{
		cct_setcolor(15, 15);
		for (j = 0; j < 3; j++)
		{
			cct_gotoxy(4 + (colnow - 1) * 8, 3 + (i - 1) * 4 - times + j);
			cout << "      ";
		}

		cct_setcolor(color, 0);
		for (j = 0; j < 3; j++)
		{
			cct_gotoxy(4 + (colnow - 1) * 8, 4 + (i - 1) * 4 - times + j);
			if (j == 0)
				cout << "┏" << "━" << "┓";
			else if (j == 1 && color <= 9)
				cout << "┃" << color << " ┃";
			else if (j==1 && color>=10)
				cout << "┃" << color << "┃";
			else
				cout << "┗" << "━" << "┛";
		}
		if ((times-1) % 4 == 0)
		{
			cct_setcolor(15, 0);
			cct_gotoxy(4 + (colnow - 1) * 8, 3 + (i - 1) * 4 - times);
			cout << "━" << "━" << "━";
		}
		Sleep(1);
	}
	Sleep(1);
}

/***************************************************************************
  函数名称：see_fall
  功    能：显示块下落的动画效果
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void see_fall(int a[10][12], int row, int col, int rownow, int colnow)
{
	int i, j, n;
	light(a, rownow, colnow, 0);
	for (j = 1; j <= col; j++)//左到右的列遍历
	{
		for (i = row; i >=2; i--)//从下往上找，第一行如果空也不用再找了
		{
			if (a[i][j] == 0)
			{
				for (n = i; n >= 1; n--)
				{
					if (a[n][j] != 0)
						break;
				}
				if (n != 0)
				{
					anime(n, i, a[n][j], j);
					a[i][j] = a[n][j];
					a[n][j] = 0;
				}
			}
		}
	}
}

void fill(int a[10][12], int tmp[10][12], int row, int col)
{
	int i, j;
	for (i = 1; i <= row; i++)
	{
		Sleep(3);
		for (j = 1; j <= col; j++)
		{
			if (tmp[i][j] == 1)
				light(a, i, j, 0);
		}
	}
}
void findtmp(int a[10][12], int tmp[10][12], int row, int col)
{
	int i, j;
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (a[i][j] == 0)
				tmp[i][j] = 1;
		}
	}
}

void wait()
{
	int ret, x, y, maction, keycode1, keycode2;
	while (1)
	{
		ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
			return;
		else if (ret == CCT_KEYBOARD_EVENT && keycode1 == '\r' && keycode2 == 0)
			return;
	}
	return;
}

void menu8(int row, int col)
{
	cct_cls();
	cct_setcursor(3);

	
	int rownow = 1, colnow = 1;
	int a[10][12] = { 0 };//初始化全部为0，最大8x10的外圈也全部为0
	int merge[10][12] = { 0 };//将要合并的坐标会变为1，和a数组保持一致坐标，方便统一处理
	int k = 0, tmp[10][12] = { 0 }, judge = 0, thisscore = 0;
	init(a, row, col);
	draw6(a, row, col);//画出带框图形
	cct_enable_mouse();
	mergeclear(merge);
	judge = various_choose(a, row, col, rownow, colnow, merge);
	if (judge)
	{
		disappear(a, row, col, rownow, colnow, merge);//片块消除
		twinkle(a, rownow, colnow);//合成中间块闪烁
		a[rownow][colnow]--;
		thisscore = score(a, merge, row, col, rownow + 'A' - 1, colnow + '0' - 1);
		a[rownow][colnow]++;
		cct_gotoxy(0, 0);
		cout << "本次得分:" << thisscore << " 总分:" << thisscore << " 合成目标:" << 5 << "           ";
		cct_gotoxy(0, row * 4 + 4);
		cout << "合成完成，回车键/单击左键下落                                                                ";
		wait();
		calc(a, merge, rownow + 'A' - 1, colnow + '0' - 1);//此时a数组是合成但未下落状态
		a[rownow][colnow]--;
		see_fall(a, row, col, rownow, colnow);//块下落
		cct_gotoxy(0, 4 * row + 4);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << "下落完成，回车键/单击左键填充新值                                                ";
		wait();
		findtmp(a, tmp, row, col);
		init(a, row, col);
		fill(a, tmp, row, col);
	}
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cct_gotoxy(0, 4 * row + 4);
	cout << "本次合成结束，按C/单击左键继续              " << endl;

	cct_setcursor(2);
	cct_gotoxy(0, 4 * row + 4);
	cout << "                                                       ";
	cct_gotoxy(0, 4 * row + 4);
	end();
}


void menu9(int row, int col, int target)
{
	cct_cls();
	cct_setcursor(3);


	int rownow = 1, colnow = 1;
	int a[10][12] = { 0 };//初始化全部为0，最大8x10的外圈也全部为0
	int merge[10][12] = { 0 };//将要合并的坐标会变为1，和a数组保持一致坐标，方便统一处理
	int k = 0, tmp[10][12] = { 0 };
	int ret = 0, x = 0, y = 0, maction = 0, keycode1 = 0, keycode2 = 0;
	int sumscore = 0, thisscore = 0, judge = 1;
	init(a, row, col);
	draw6(a, row, col);//画出带框图形
	cct_enable_mouse();
	while (judge)
	{
		mergeclear(tmp);
		mergeclear(merge);
		judge = various_choose(a, row, col, rownow, colnow, merge);
		if (judge)
		{
			disappear(a, row, col, rownow, colnow, merge);//片块消除
			twinkle(a, rownow, colnow);//合成中间块闪烁
			a[rownow][colnow]--;
			thisscore = score(a, merge, row, col, rownow + 'A' - 1, colnow + '0' - 1);
			a[rownow][colnow]++;
			calc(a, merge, rownow + 'A' - 1, colnow + '0' - 1);//此时a数组是合成但未下落状态
			a[rownow][colnow]--;
			see_fall(a, row, col, rownow, colnow);//块下落
			findtmp(a, tmp, row, col);
			init(a, row, col);
			fill(a, tmp, row, col);

			cct_gotoxy(0, 0);
			sumscore += thisscore;
			cout << "本次得分:" << thisscore << " 总分:" << sumscore << " 合成目标:" << target << "           ";

			
			if (win(a, target))
			{
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "已经合成到" << target << ",";
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << "按回车键/单击左键继续向更高目标前进                        " << endl;
				target++;
				while (1)
				{
					ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
					if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
						break;
					else if (ret == CCT_KEYBOARD_EVENT && keycode1 == '\r' && keycode2 == 0)
						break;
				}
				cct_gotoxy(0, 0);
				cout << "本次得分:" << thisscore << " 总分:" << sumscore << " 合成目标:" << target << "             ";
			}
			if (lose(a, row, col))
			{
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "无可合并的项，游戏结束！                ";
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << "按Q退出                        ";
				while (1)
				{
					char ch = _getch();
					if (ch == 'q' || ch == 'Q')
					{
						k = 1;
						break;
					}
				}
			}
			if (k == 1)
				break;
		}
	}


	cct_setcursor(2);
	cct_gotoxy(0, row * 4 + 4);
	end();
}