#include <iostream>
#include <conio.h>

#include "90-b2.h"
#include "cmd_console_tools.h"
#include "lib_mto10_net_tools.h"

using namespace std;

char mto10_menu()
{
	char menu;
	cout << "---------------------------------------" << endl;
	cout << "1.命令行找出可合成项并标识（非递归）" << endl;
	cout << "2.命令行找出可合成项并标识（递归）" << endl;
	cout << "3.命令行完成一次合成（分步骤显示）" << endl;
	cout << "4.命令行完整版（分步骤显示）" << endl;
	cout << "5.伪图形界面显示初始数组（无分隔线）" << endl;
	cout << "6.伪图形界面显示初始数组（有分隔线）" << endl;
	cout << "7.伪图形界面下用箭头键/鼠标选择当前色块" << endl;
	cout << "8.伪图形界面完成一次合成（分步骤）" << endl;
	cout << "9.伪图形界面完整版(支持鼠标)" << endl;
	cout << "---------------------------------------" << endl;
	cout << "A.命令行界面（网络自动解-基本版）" << endl;
	cout << "B.伪图形界面（网络自动解-基本版）" << endl;
	cout << "---------------------------------------" << endl;
	cout << "0.退出" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[请选择:] ";
	while (1)
	{
		menu = _getch();
		if ((menu >= '0' && menu <= '9') || (menu >= 'A' && menu <= 'B') || (menu >= 'a' && menu <= 'b'))
		{
			cout<<menu;
			break;
		}
	}
	if (menu >= 'a' && menu <= 'b')
		menu = menu - 'a' + 'A';//转成大写
	return menu;
}
int main()
{
	cct_setfontsize("新宋体", 12, 6);
	cct_setconsoleborder(45, 27);
	char menu;
	int row = 0, col = 0, target = 0;
	while (1)
	{
		cct_cls();
		menu = mto10_menu();
		if (menu == '0')
			break;
		cct_cls();
		getcrt(&row, &col, &target, menu);//获得行列等参数
		cct_setconsoleborder(8 * (col + 1)+6, 5 * row + 2);
		if (menu == '1')
			menu1(row, col);
		else if (menu == '2')
			menu2(row, col);
		else if (menu == '3')
			menu3(row, col, target);
		else if (menu == '4')
			menu4(row, col, target);
		else if (menu == '5')
			menu5(row, col);
		else if (menu == '6')
			menu6(row, col);
		else if (menu == '7')
			menu7(row, col);
		else if (menu == '8')
			menu8(row, col);
		else if (menu == '9')
			menu9(row, col, target);
		else if (menu == 'A')
		{
			cct_setconsoleborder(8 * (col + 2), 5 * row + 2);
			domenu(row, col, 'A');
		}
		else if (menu == 'B')
		{
			cct_setconsoleborder(8 * (col + 2), 5 * row + 92);
			domenu(row, col, 'B');
		}


	}




	cct_gotoxy(0, 20);
	system("pause");




	return 0;
}