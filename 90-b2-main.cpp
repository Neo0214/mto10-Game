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
	cout << "1.�������ҳ��ɺϳ����ʶ���ǵݹ飩" << endl;
	cout << "2.�������ҳ��ɺϳ����ʶ���ݹ飩" << endl;
	cout << "3.���������һ�κϳɣ��ֲ�����ʾ��" << endl;
	cout << "4.�����������棨�ֲ�����ʾ��" << endl;
	cout << "5.αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�" << endl;
	cout << "6.αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�" << endl;
	cout << "7.αͼ�ν������ü�ͷ��/���ѡ��ǰɫ��" << endl;
	cout << "8.αͼ�ν������һ�κϳɣ��ֲ��裩" << endl;
	cout << "9.αͼ�ν���������(֧�����)" << endl;
	cout << "---------------------------------------" << endl;
	cout << "A.�����н��棨�����Զ���-�����棩" << endl;
	cout << "B.αͼ�ν��棨�����Զ���-�����棩" << endl;
	cout << "---------------------------------------" << endl;
	cout << "0.�˳�" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[��ѡ��:] ";
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
		menu = menu - 'a' + 'A';//ת�ɴ�д
	return menu;
}
int main()
{
	cct_setfontsize("������", 12, 6);
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
		getcrt(&row, &col, &target, menu);//������еȲ���
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