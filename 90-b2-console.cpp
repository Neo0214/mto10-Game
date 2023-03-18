#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include "90-b2.h"
#include "cmd_console_tools.h"
using namespace std;
/***************************************************************************
  �������ƣ�draw
  ��    �ܣ���ӡ�ޱ߿�ͼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void draw(int a[10][12], int row, int col)
{
	int i, j;
	cout << "��ǰ��Ļ����Ϊ��" << 5 * row + 2 << "��" << 8 * (col + 1) << "��                  " << endl;
	cout << "      " << 0;
	for (j = 1; j < col; j++)
		cout << setw(6) << j;//�����һ������
	cout << "\n  ";
	for (j = 0; j < col * 3 + 2; j++)
	{
		cct_setcolor(15, 0);
		if (j == 0)
			cout << "��";
		else if (j == col * 3 + 1)
			cout << "��";
		else
			cout << "��";
	}//��ӡ����
	cout << endl;
	Sleep(2);
	for (i = 1; i < (row * 3 + 2); i++)//һ������������ȥ��λ��
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
				cout << "��";
			else
				cout << "  ";
			Sleep(1);
		}
		cout << endl;
		cct_setcolor(0, 7);
		Sleep(2);
	}
	cout << "  ";
	for (j = 0; j < col * 3 + 2; j++)//��ӡβ��
	{
		cct_setcolor(15, 0);
		if (j == 0)
			cout << "��";
		else if (j == col * 3 + 1)
			cout << "��";
		else
			cout << "��";
	}
	cout << endl;
	for (i = 0; i < row * 3; i++)
	{
		Sleep(2);
		cct_gotoxy(4, 3 + i);
		for (j = 0; j < col; j++)
		{
			cct_setcolor(a[i/3+1][j+1], 0);
			if (i % 3 == 0)//����
				cout << "��" << "��" << "��";
			else if ((i - 1) % 3 == 0)
				cout << "��" << a[i/3+1][j+1] << " " << "��";
			else
				cout << "��" << "��" << "��";
		}
	}
	cout << "\n\n";
	cct_setcolor(0, 7);
}

void menu5(int row, int col)
{
	cct_cls();
	int a[10][12] = { 0 }, k = 0;//��ʼ��ȫ��Ϊ0�����8x10����ȦҲȫ��Ϊ0
	int merge[10][12] = { 0 };//��Ҫ�ϲ���������Ϊ1����a���鱣��һ�����꣬����ͳһ����
	char getrow = 0, getcol = 0;//����ϲ�����
	init(a, row, col);
	draw(a, row, col);
	end();
}
/***************************************************************************
  �������ƣ�draw6
  ��    �ܣ���ӡ�б߿�ͼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void draw6(int a[10][12], int row, int col)
{
	int i, j;
	cout << "��ǰ��Ļ����Ϊ��" << 5 * row + 2 << "��" << 8 * (col + 1) << "��" << endl;
	cout << "      0";
	for (i = 1; i < col; i++)
		cout << setw(8) << i;
	cout << "\n  ";
	for (j = 0; j < col * 4 + 1; j++)
	{
		cct_setcolor(15, 0);
		if (j == 0)
			cout << "��";
		else if (j == col * 4)
			cout << "��";
		else if (j % 4 == 0)
			cout << "��";
		else
			cout << "��";
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
				cout << "��";
			else if (j % 4 != 0 && i % 4 == 0)
				cout << "��";
			else if (j % 4 == 0 && i % 4 == 0 && j != 0 && j != 4 * col)
				cout << "��";
			else if (j == 0 && i % 4 == 0)
				cout << "��";
			else
				cout << "��";
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
			cout << "��";
		else if (j == col * 4)
			cout << "��";
		else if (j % 4 == 0)
			cout << "��";
		else
			cout << "��";
	}
	//�װ�
	int basey = 3, basex = 4, x, y, n;
	for (i = 1; i <= row; i++)
	{
		Sleep(1);
		for (j = 1; j <= col; j++)//��ӡ��Ԫ��Ԫ�ؿ�
		{
			Sleep(1);
			x = basex + 8 * (j - 1);
			y = basey + 4 * (i - 1);
			cct_setcolor(a[i][j], 0);
			for (n = 0; n < 3; n++)
			{
				cct_gotoxy(x, y + n);
				if (n == 0)
					cout << "������";
				else if (n == 1)
					cout << "��" << a[i][j] << " ��";
				else
					cout << "������";
			}
			
		}
	}



	cct_setcolor(0, 7);
	cout << "\n\n";
	
}

void menu6(int row, int col)
{
	cct_cls();
	int a[10][12] = { 0 }, k = 0;//��ʼ��ȫ��Ϊ0�����8x10����ȦҲȫ��Ϊ0
	int merge[10][12] = { 0 };//��Ҫ�ϲ���������Ϊ1����a���鱣��һ�����꣬����ͳһ����
	init(a, row, col);
	draw6(a, row, col);
	end();
}
/***************************************************************************
  �������ƣ�light
  ��    �ܣ���������ĳ��ָ�������
  ���������
  �� �� ֵ��
  ˵    ����
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
			cout << "������";
		else if (n == 1 && a[rownow][colnow] <= 9)
			cout << "��" << a[rownow][colnow] << " ��";
		else if (n == 1 && a[rownow][colnow] >= 10)
			cout << "��" << a[rownow][colnow] << "��";
		else
			cout << "������";
	}
	cct_setcolor(0, 7);
}
/***************************************************************************
  �������ƣ�judge_mouse
  ��    �ܣ��������λ�ú�״̬��ʱ������Ļ�ϵ���ʾ״̬
  ���������
  �� �� ֵ��1˵���Ϸ�λ�ã�0λ�÷Ƿ�
  ˵    ����ֻ�ϲ���
***************************************************************************/
int judge_mouse(int a[10][12], int x, int y, int row, int col, int* rownow, int* colnow)
{
	int starow = *rownow, stacol = *colnow;//��¼��ǰ����λ��
	x = x - 2;
	y = y - 2;//���Ͻǵ�һ��ɫ�鵱��(0,0)
	if ((y % 4 != 0 && y <= row * 4 && y > 0) && (x % 8 != 0 && (x - 1) % 8 != 0 && x > 0 && x < col * 8))
	{
		*rownow = y / 4 + 1;
		*colnow = x / 8 + 1;//��ȡ��ǰ�����������
		if (*rownow != starow || *colnow != stacol)//������������仯
		{
			light(a, starow, stacol, COLOR_BLACK);
			light(a, *rownow, *colnow, COLOR_HWHITE);
			starow = *rownow;
			stacol = *colnow;
			cct_setcolor(0, 7);
			cct_gotoxy(0, row * 4 + 4);
			cout << "[��ǰ���] " << char('A' + *rownow - 1) << "��" << *colnow - 1 << "��                                          ";
		}
		else//��������򲻷����仯
		{
			light(a, *rownow, *colnow, COLOR_HWHITE);
			cct_setcolor(0, 7);
			cct_gotoxy(0, row * 4 + 4);
			cout << "[��ǰ���] " << char('A' + *rownow - 1) << "��" << *colnow - 1 << "��                                         ";
		}
		return 1;
	}
	else
	{
		light(a, starow, stacol, COLOR_BLACK);
		cct_setcolor(0, 7);
		cct_gotoxy(0, row * 4 + 4);
		cout << "[��ǰ���] λ�÷Ƿ�                                                       ";
		return 0;
	}
	
}
/***************************************************************************
  �������ƣ�judge_key
  ��    �ܣ����ݼ���״̬��ʱ������Ļ�ϵ���ʾ״̬
  ���������
  �� �� ֵ�������ڷǷ�λ�ã���Զ����1
  ˵    ����ֻ�ϲ���
***************************************************************************/
int judge_key(int a[10][12], int keycode1, int keycode2, int row, int col, int* rownow, int* colnow)
{
	int starow = *rownow, stacol = *colnow;//��¼��ǰ����λ��
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
	cout << "[��ǰ����] " << char('A' + *rownow - 1) << "��" << *colnow-1 << "��                                   ";
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
	int a[10][12] = { 0 };//��ʼ��ȫ��Ϊ0�����8x10����ȦҲȫ��Ϊ0
	int merge[10][12] = { 0 };//��Ҫ�ϲ���������Ϊ1����a���鱣��һ�����꣬����ͳһ����
	init(a, row, col);
	draw6(a, row, col);//��������ͼ��
	cct_enable_mouse();
	light(a, rownow, colnow, COLOR_HWHITE);//�������ϽǵĿ�
	while (1)
	{
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT)//��ʹ�����
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
			cout << "ѡ����" << char('A' + rownow - 1) << "��" << colnow - 1 << "��          " << endl;
			break;
		}
		else if (ret == CCT_MOUSE_EVENT && maction == MOUSE_RIGHT_BUTTON_CLICK)
		{
			cct_gotoxy(0, row * 4 + 4);
			cout << "ѡ����" << char('A' + rownow - 1) << "��" << colnow - 1 << "��          " << endl;
			break;
		}
		else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 13 && keycode2 == 0)
		{
			cct_gotoxy(0, row * 4 + 4);
			cout << "ѡ����" << char('A' + rownow - 1) << "��" << colnow - 1 << "��              " << endl;
			break;
		}
		else if (ret == CCT_KEYBOARD_EVENT && (keycode1 == 'q' || keycode1 == 'Q') && keycode2 == 0)
		{
			cct_gotoxy(0, row * 4 + 4);
			cout << "ѡ����" << char('A' + rownow - 1) << "��" << colnow - 1 << "��          " << endl;
			break;
		}
	}
	cct_setcursor(2);
	end();
}
/***************************************************************************
  �������ƣ�scan
  ��    �ܣ�����һ��ѡ��λ�ý�Ҫ��ȥ�Ŀ����ε���
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�range
  ��    �ܣ��ж�����Ƿ�����ȷλ������û�зŵ���������
  ���������
  �� �� ֵ����ȷ����1�����󷵻�0
  ˵    ����
***************************************************************************/
int range(int x, int y, int rownow, int colnow, int row, int col)
{
	x = x - 2;
	y = y - 2;//���Ͻǵ�һ��ɫ�鵱��(0,0)
	if ((y % 4 != 0 && y <= row * 4 && y > 0) && (x % 8 != 0 && (x - 1) % 8 != 0 && x > 0 && x < col * 8))
	{//����ȷ��Χ��
		if (rownow == y / 4 + 1 && colnow == x / 8 + 1)
			return 1;
	}
	return 0;
}
/***************************************************************************
  �������ƣ�various_choose
  ��    �ܣ����϶�ȡ���̺����״̬���������õȾ��岽��
  ���������
  �� �� ֵ��
  ˵    ����
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
		if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)//��궯��
		{
			k = judge_mouse(a, x, y, row, col, &rownow, &colnow);
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			k = judge_key(a, keycode1, keycode2, row, col, &rownow, &colnow);
		}
		//k=0ʲôҲ������k!=0����

		ev = findmerge(a, rownow + 'A' - 1, colnow + '0' - 1, row, col, merge);//��ȡ��ǰ�����Ƿ��ǿ��ԺϳɵĿ�
		if (k && ret==CCT_MOUSE_EVENT && maction==MOUSE_LEFT_BUTTON_CLICK)
		{
			if (ev)//��ǰ����Ժϳ�
			{
				cct_gotoxy(0, row * 4 + 4);
				cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����";
				judge = 1;
			}
			else//��ǰ�鲻�ܺϳ�
			{
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "��Χ����ֵͬ                                    ";
				judge = 2;
			}
		}
		else if (k && ret == CCT_KEYBOARD_EVENT && keycode1 == '\r' && keycode2 == 0)
		{
			if (ev)
			{
				cct_gotoxy(0, row * 4 + 4);
				cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����";
				judge = 1;
			}
			else
			{
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "��Χ����ֵͬ                                         ";
				judge = 2;
			}
		}
		if (judge == 1)//��ǰ����Ժϳ�ʱ���������򣬵ȴ�����ȷ��
		{
			scan(a, merge, row, col, COLOR_WHITE, rownow, colnow);
			while (1)
			{
				ret = cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT && maction == MOUSE_ONLY_MOVED)
				{
					if (!range(x, y, rownow, colnow, row, col))//λ�ñ仯
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
  �������ƣ�disappear
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
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
						cout << "��" << "��" << "��";
					else if (n == 1 && a[i][j] <= 9)
						cout << "��" << a[i][j] << " ��";
					else if (n==1 && a[i][j]>=10)
						cout << "��" << a[i][j] << "��";
					else
						cout << "��" << "��" << "��";
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
{//�ӵ�n���䵽��i�У���ɫΪcolor
	int times, j;
	for (times = (i - n) * 4; times > 0; times--)//һ��Ҫ���ش�ӡ������Щ����
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
				cout << "��" << "��" << "��";
			else if (j == 1 && color <= 9)
				cout << "��" << color << " ��";
			else if (j==1 && color>=10)
				cout << "��" << color << "��";
			else
				cout << "��" << "��" << "��";
		}
		if ((times-1) % 4 == 0)
		{
			cct_setcolor(15, 0);
			cct_gotoxy(4 + (colnow - 1) * 8, 3 + (i - 1) * 4 - times);
			cout << "��" << "��" << "��";
		}
		Sleep(1);
	}
	Sleep(1);
}

/***************************************************************************
  �������ƣ�see_fall
  ��    �ܣ���ʾ������Ķ���Ч��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void see_fall(int a[10][12], int row, int col, int rownow, int colnow)
{
	int i, j, n;
	light(a, rownow, colnow, 0);
	for (j = 1; j <= col; j++)//���ҵ��б���
	{
		for (i = row; i >=2; i--)//���������ң���һ�������Ҳ����������
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
	int a[10][12] = { 0 };//��ʼ��ȫ��Ϊ0�����8x10����ȦҲȫ��Ϊ0
	int merge[10][12] = { 0 };//��Ҫ�ϲ���������Ϊ1����a���鱣��һ�����꣬����ͳһ����
	int k = 0, tmp[10][12] = { 0 }, judge = 0, thisscore = 0;
	init(a, row, col);
	draw6(a, row, col);//��������ͼ��
	cct_enable_mouse();
	mergeclear(merge);
	judge = various_choose(a, row, col, rownow, colnow, merge);
	if (judge)
	{
		disappear(a, row, col, rownow, colnow, merge);//Ƭ������
		twinkle(a, rownow, colnow);//�ϳ��м����˸
		a[rownow][colnow]--;
		thisscore = score(a, merge, row, col, rownow + 'A' - 1, colnow + '0' - 1);
		a[rownow][colnow]++;
		cct_gotoxy(0, 0);
		cout << "���ε÷�:" << thisscore << " �ܷ�:" << thisscore << " �ϳ�Ŀ��:" << 5 << "           ";
		cct_gotoxy(0, row * 4 + 4);
		cout << "�ϳ���ɣ��س���/�����������                                                                ";
		wait();
		calc(a, merge, rownow + 'A' - 1, colnow + '0' - 1);//��ʱa�����Ǻϳɵ�δ����״̬
		a[rownow][colnow]--;
		see_fall(a, row, col, rownow, colnow);//������
		cct_gotoxy(0, 4 * row + 4);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << "������ɣ��س���/������������ֵ                                                ";
		wait();
		findtmp(a, tmp, row, col);
		init(a, row, col);
		fill(a, tmp, row, col);
	}
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cct_gotoxy(0, 4 * row + 4);
	cout << "���κϳɽ�������C/�����������              " << endl;

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
	int a[10][12] = { 0 };//��ʼ��ȫ��Ϊ0�����8x10����ȦҲȫ��Ϊ0
	int merge[10][12] = { 0 };//��Ҫ�ϲ���������Ϊ1����a���鱣��һ�����꣬����ͳһ����
	int k = 0, tmp[10][12] = { 0 };
	int ret = 0, x = 0, y = 0, maction = 0, keycode1 = 0, keycode2 = 0;
	int sumscore = 0, thisscore = 0, judge = 1;
	init(a, row, col);
	draw6(a, row, col);//��������ͼ��
	cct_enable_mouse();
	while (judge)
	{
		mergeclear(tmp);
		mergeclear(merge);
		judge = various_choose(a, row, col, rownow, colnow, merge);
		if (judge)
		{
			disappear(a, row, col, rownow, colnow, merge);//Ƭ������
			twinkle(a, rownow, colnow);//�ϳ��м����˸
			a[rownow][colnow]--;
			thisscore = score(a, merge, row, col, rownow + 'A' - 1, colnow + '0' - 1);
			a[rownow][colnow]++;
			calc(a, merge, rownow + 'A' - 1, colnow + '0' - 1);//��ʱa�����Ǻϳɵ�δ����״̬
			a[rownow][colnow]--;
			see_fall(a, row, col, rownow, colnow);//������
			findtmp(a, tmp, row, col);
			init(a, row, col);
			fill(a, tmp, row, col);

			cct_gotoxy(0, 0);
			sumscore += thisscore;
			cout << "���ε÷�:" << thisscore << " �ܷ�:" << sumscore << " �ϳ�Ŀ��:" << target << "           ";

			
			if (win(a, target))
			{
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "�Ѿ��ϳɵ�" << target << ",";
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << "���س���/����������������Ŀ��ǰ��                        " << endl;
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
				cout << "���ε÷�:" << thisscore << " �ܷ�:" << sumscore << " �ϳ�Ŀ��:" << target << "             ";
			}
			if (lose(a, row, col))
			{
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
				cout << "�޿ɺϲ������Ϸ������                ";
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << "��Q�˳�                        ";
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