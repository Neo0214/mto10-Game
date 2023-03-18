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
	//将当前地图情况存入数组a
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
	char svrpack[RECVBUF_LEN];	//存放从Server端收到的数据
	char row;
	int col;
	int a[10][12] = { 0 }, merge[10][12] = { 0 }, i, j, tmp[10][12] = { 0 };

	while (1) {
		
		
		
		/* 游戏已结束则不再读键*/
		if (client.is_gameover())
			break;

		
		//应在此处求解row与col
		auto_calculation(row, col, client);//求解row和col

		if (menu == 'B')//获取解坐标后，不用发送给服务器，直接将动画前半部分完成
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
			disappear(a, client.get_row(), client.get_col(), row - 'A' + 1, col+1, merge);//片块消除
			twinkle(a, row - 'A' + 1, col+1);//合成中间块闪烁
			calc(a, merge, row, col + '0');
			a[row - 'A' + 1][col+1]--;
			see_fall(a, client.get_row(), client.get_col(), row - 'A' + 1, col+1);//块下落
			cct_gotoxy(0, client.get_row() * 4 + 3);
			cct_setcolor(0, 7);
		}


		client.send_coordinate(row, col);//将解发给服务器

		/* -------------------
			Server=>Client
		   ------------------- */
		   /* 等待Server端的gameprogress */
		if (client.get_gameprogress_string(svrpack) < 0) {
			return -1;
		}
		//将解发送给服务器，获取服务器反馈

		Sleep(50);
		if (menu == 'A')
		{
			cct_cls();
			client.print_map(); //本函数仅为示意，图形界面中不能调用，要自己写转换函数
		}
		
		cout << "Server应答 : " << endl << svrpack;
		if (menu == 'B')//获取随机生成部分后，完成后半部分动画
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
		
		

		

		/* 打印出 svrpack 的内容，自行处理，并向Server端继续反馈
		   根据 Content 的内容，解释如下：
			"InvalidCoordinate" : 非法坐标
				GameID		：本次游戏ID
				Step		：目前步数
				Score		：目前分数
				MaxValue	：目前合成的最大值
			"MergeFailed" : 选择的坐标周围无可合成项
				GameID		：本次游戏ID
				Step		：目前步数
				Score		：目前分数
				MaxValue	：目前合成的最大值
			"MergeSucceeded" : 本次合成成功
				GameID		：本次游戏ID
				Step		：目前步数
				Score		：目前分数
				MaxValue	：目前合成的最大值
				OldMap		：消除选择坐标后的地图
				NewMap		：消除选择坐标后再次填充的地图
			"GameOver" : 地图上无消除项，游戏结束
				GameID			：本次游戏ID
				FinalStep		：最终步数
				FinalScore		：最终分数
				FinalMaxValue	：最终合成的最大值
			"GameFinished" : 已合成到设置上限（16），游戏完成
				GameID			：本次游戏ID
				FinalStep		：最终步数
				FinalScore		：最终分数
				FinalMaxValue	：最终合成的最大值 */

				/* 打印收到的原始字符串 */
		
		



		
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
			Sleep(0);
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
		Sleep(0);
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





/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void domenu(int row, int col, char menu)
{
	cct_setcursor(3);
	const char* my_no = "";		//本人学号
	const char* my_pwd = "";	//本人密码

	int wanted_row, wanted_col, wanted_id, wanted_delay;
#if 1 //条件编译，此处改为 #if 0 则表示启用下面 #else 中的语句
	wanted_row = row;			//此处按需修改为键盘输入等形式
	wanted_col = col;			//此处按需修改为键盘输入等形式
	wanted_id = -1;		//id为本次请求的游戏序号，如果置-1，表示服务器随机产生，[0..2^31-1]则表示想固定序号（序号固定，则每次给出的初始矩阵及后续填充均相同，方便调试）
	wanted_delay = 60 * 1000;	//delay为请求的每步应答的最长时延，单位ms
#else
	wanted_row = -1;
	wanted_col = -1;
	wanted_id = -1;
	wanted_delay = -1;
#endif
	mto10_net_tools client;

	/* 打开client类对象中的debug开关（调试时可打开，到图形界面时需关闭） */
	client.set_debug_switch(false);

	/* 连接服务器 */
	if (client.connect() < 0) {
		/* 连接失败信息，有没有debug_switch都打印 */
		cout << "连接服务器失败!" << endl;
		return;
	}

	/* 向Server端发送认证信息及参数 */
	if (client.send_parameter(my_no, '*', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
		cout << "发送认证及参数信息失败!" << endl;
		return;
	}

	/* 等待Server端下发参数（游戏开始）*/
	if (client.wait_for_game_start() < 0) {
		cout << "等待GameStart失败!" << endl;
		return;
	}

	/* 打印从服务器收到的参数，本次游戏以此参数为准（例：发送6行6列，返回8行10列，则本次游戏以8行10列为准）
	   下面打印的信息，图形化界面可以自行去除 */
	//cout << "服务器返回信息 : " << endl;
	//cout << "  行数 : " << client.get_row() << endl;
	//cout << "  列数 : " << client.get_col() << endl;
	//cout << "  ID号 : " << client.get_gameid() << endl;
	//cout << "  超时 : " << client.get_delay() / 1000.0 << "(秒)" << endl;
	//cout << "  地图 : " << client.get_map() << endl;
	/* 地图串中的值为1-9，A-F，分别表示1-15的值，
		   例如：
			 服务器返回行=3
			 服务器返回列=4
			 服务器返回地图=123A85CF2123
		   则表示当前地图为(本例仅仅是示例)
			 1 2 3  10
			 8 5 12 15
			 2 1 2  3
			游戏结束的条件为：合成到16或无任何可合成元素 */

			/* 进入游戏交互环节
			   1、收到Server的GameOver则返回0，游戏结束
			   2、其它错误均返回-1（报文信息不正确等错误），重连，再次重复	*/
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
	cout << "游戏结束" << endl;
	end();
	return;
}