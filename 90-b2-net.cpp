#include "lib_mto10_net_tools.h"
#include "cmd_console_tools.h"
#include "90-b2.h"
#include <iostream>
#include <iomanip>

#define		MAX_ROW_NUM		8
#define		MAX_COL_NUM		10

using namespace std;

int getscore(int merge[10][12], int realrow, int realcol, int iin, int jin)
{
	int i, j, sum = 0;
	for (i = 1; i <= realrow; i++)
	{
		for (j = 1; j <= realcol; j++)
		{
			if (merge[i][j] == 1)
				sum++;
		}
	}
	return sum;
}
int auto_calculation(char &row, int &col, mto10_net_tools& client)
{
	int realrow, realcol;
	realrow = client.get_row();
	realcol = client.get_col();
	int a[10][12] = { 0 };
	int merge[10][12] = { 0 };
	int i, j, max = 1;
	int sum = 0;
	bool k = true;
	for (i = 1; i <= realrow; i++)
	{
		for (j = 1; j <= realcol; j++)
			a[i][j] = *(client.get_map()+(i-1)*realcol+(j-1))-'0';
	}
	//����ǰ��ͼ�����������a
	while (k)
	{
		for (i = realrow; i >=1; i--)
		{
			for (j = 1; j <=realcol; j++)
			{
				mergeclear(merge);
				if (a[i][j]==max && findmerge(a, i - 1 + 'A', j - 1 + '0', realrow, realcol, merge))
				{
					k = false;
					if (sum < getscore(merge, realrow, realcol, i, j))
					{
						sum = getscore(merge, realrow, realcol, i, j);
						row = i - 1 + 'A';
						col = j - 1;
					}
				}
			}
		}
		max++;
		if (max == 17)
			break;
	}
	return 0;
}





int game_progress(mto10_net_tools& client, char menu)
{
	char svrpack[RECVBUF_LEN];	//��Ŵ�Server���յ�������
	char row;
	int col;
	int a[10][12] = { 0 }, merge[10][12] = { 0 }, i, j, tmp[10][12] = { 0 };

	while (1) {
		
		
		
		/* ��Ϸ�ѽ������ٶ���*/
		if (client.is_gameover())
			break;

		
		//Ӧ�ڴ˴����row��col
		auto_calculation(row, col, client);//���row��col

		if (menu == 'B')//��ȡ������󣬲��÷��͸���������ֱ�ӽ�����ǰ�벿�����
		{
			mergeclear(merge);
			mergeclear(a);
			mergeclear(tmp);
			for (i = 1; i <= client.get_row(); i++)
			{
				for (j = 1; j <= client.get_col(); j++)
					a[i][j] = *(client.get_map() + (i - 1) * client.get_col() + (j - 1)) - '0';
			}
			findmerge(a, row, col + '0', client.get_row(), client.get_col(), merge);
			disappear(a, client.get_row(), client.get_col(), row - 'A' + 1, col+1, merge);//Ƭ������
			twinkle(a, row - 'A' + 1, col+1);//�ϳ��м����˸
			calc(a, merge, row, col + '0');
			a[row - 'A' + 1][col+1]--;
			see_fall(a, client.get_row(), client.get_col(), row - 'A' + 1, col+1);//������
			cct_gotoxy(0, client.get_row() * 4 + 3);
			cct_setcolor(0, 7);
		}


		client.send_coordinate(row, col);//���ⷢ��������

		/* -------------------
			Server=>Client
		   ------------------- */
		   /* �ȴ�Server�˵�gameprogress */
		if (client.get_gameprogress_string(svrpack) < 0) {
			return -1;
		}
		//���ⷢ�͸�����������ȡ����������

		Sleep(50);
		if (menu == 'A')
		{
			cct_cls();
			client.print_map(); //��������Ϊʾ�⣬ͼ�ν����в��ܵ��ã�Ҫ�Լ�дת������
		}
		
		cout << "ServerӦ�� : " << endl << svrpack;
		if (menu == 'B')//��ȡ������ɲ��ֺ���ɺ�벿�ֶ���
		{
			findtmp(a, tmp, client.get_row(), client.get_col());
			for (i = 1; i <= client.get_row(); i++)
			{
				for (j = 1; j <= client.get_col(); j++)
					a[i][j] = *(client.get_map() + (i - 1) * client.get_col() + (j - 1)) - '0';
			}
			fill(a, tmp, client.get_row(), client.get_col());
			Sleep(1000);
			cct_gotoxy(0, client.get_row() * 4 + 3);
		}
		
		

		

		/* ��ӡ�� svrpack �����ݣ����д�������Server�˼�������
		   ���� Content �����ݣ��������£�
			"InvalidCoordinate" : �Ƿ�����
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
			"MergeFailed" : ѡ���������Χ�޿ɺϳ���
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
			"MergeSucceeded" : ���κϳɳɹ�
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
				OldMap		������ѡ�������ĵ�ͼ
				NewMap		������ѡ��������ٴ����ĵ�ͼ
			"GameOver" : ��ͼ�����������Ϸ����
				GameID			��������ϷID
				FinalStep		�����ղ���
				FinalScore		�����շ���
				FinalMaxValue	�����պϳɵ����ֵ
			"GameFinished" : �Ѻϳɵ��������ޣ�16������Ϸ���
				GameID			��������ϷID
				FinalStep		�����ղ���
				FinalScore		�����շ���
				FinalMaxValue	�����պϳɵ����ֵ */

				/* ��ӡ�յ���ԭʼ�ַ��� */
		
		



		
	}//end of while(1)

	return 0;
}

void drawnet(int a[10][12], int row, int col)
{
	int i, j;
	cout << endl;
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
			Sleep(0);
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
		Sleep(0);
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





/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void domenu(int row, int col, char menu)
{
	cct_setcursor(3);
	const char* my_no = "";		//����ѧ��
	const char* my_pwd = "";	//��������

	int wanted_row, wanted_col, wanted_id, wanted_delay;
#if 1 //�������룬�˴���Ϊ #if 0 ���ʾ�������� #else �е����
	wanted_row = row;			//�˴������޸�Ϊ�����������ʽ
	wanted_col = col;			//�˴������޸�Ϊ�����������ʽ
	wanted_id = -1;		//idΪ�����������Ϸ��ţ������-1����ʾ���������������[0..2^31-1]���ʾ��̶���ţ���Ź̶�����ÿ�θ����ĳ�ʼ���󼰺���������ͬ��������ԣ�
	wanted_delay = 60 * 1000;	//delayΪ�����ÿ��Ӧ����ʱ�ӣ���λms
#else
	wanted_row = -1;
	wanted_col = -1;
	wanted_id = -1;
	wanted_delay = -1;
#endif
	mto10_net_tools client;

	/* ��client������е�debug���أ�����ʱ�ɴ򿪣���ͼ�ν���ʱ��رգ� */
	client.set_debug_switch(false);

	/* ���ӷ����� */
	if (client.connect() < 0) {
		/* ����ʧ����Ϣ����û��debug_switch����ӡ */
		cout << "���ӷ�����ʧ��!" << endl;
		return;
	}

	/* ��Server�˷�����֤��Ϣ������ */
	if (client.send_parameter(my_no, '*', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
		cout << "������֤��������Ϣʧ��!" << endl;
		return;
	}

	/* �ȴ�Server���·���������Ϸ��ʼ��*/
	if (client.wait_for_game_start() < 0) {
		cout << "�ȴ�GameStartʧ��!" << endl;
		return;
	}

	/* ��ӡ�ӷ������յ��Ĳ�����������Ϸ�Դ˲���Ϊ׼����������6��6�У�����8��10�У��򱾴���Ϸ��8��10��Ϊ׼��
	   �����ӡ����Ϣ��ͼ�λ������������ȥ�� */
	//cout << "������������Ϣ : " << endl;
	//cout << "  ���� : " << client.get_row() << endl;
	//cout << "  ���� : " << client.get_col() << endl;
	//cout << "  ID�� : " << client.get_gameid() << endl;
	//cout << "  ��ʱ : " << client.get_delay() / 1000.0 << "(��)" << endl;
	//cout << "  ��ͼ : " << client.get_map() << endl;
	/* ��ͼ���е�ֵΪ1-9��A-F���ֱ��ʾ1-15��ֵ��
		   ���磺
			 ������������=3
			 ������������=4
			 ���������ص�ͼ=123A85CF2123
		   ���ʾ��ǰ��ͼΪ(����������ʾ��)
			 1 2 3  10
			 8 5 12 15
			 2 1 2  3
			��Ϸ����������Ϊ���ϳɵ�16�����κοɺϳ�Ԫ�� */

			/* ������Ϸ��������
			   1���յ�Server��GameOver�򷵻�0����Ϸ����
			   2���������������-1��������Ϣ����ȷ�ȴ��󣩣��������ٴ��ظ�	*/
	int a[10][12] = { 0 };
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
			a[i][j] = *(client.get_map() + (i - 1) * col + (j - 1)) - '0';
	}
	if (menu == 'B')
		drawnet(a, row, col);
	if (game_progress(client,menu) < 0) {
		end();
		client.close();
		return;
	}

	client.close();
	cout << "��Ϸ����" << endl;
	end();
	return;
}