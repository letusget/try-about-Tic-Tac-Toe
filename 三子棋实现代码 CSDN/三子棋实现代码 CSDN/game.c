#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COL 3
#define ROW 3

void menu(void);
void input(void);
void game(void);
void Initboard(char board[ROW][COL], int row, int col);
void DisplayBoard(char board[ROW][COL], int row, int col);
void PlayerMove(char board[ROW][COL], int row, int col);
void ComputerMove(char board[ROW][COL], int row, int col);
char IsWin(char board[ROW][COL], int row, int col);
int IsFull(char board[ROW][COL], int row, int col);

void main(void)
{

	input();
	
	
}

void menu(void) 
{
	printf("*********************\n");
	printf("****** 1 .开始 ******\n");
	printf("****** 2 .退出 ******\n");
	printf("*********************\n");
}

void input(void)
{
	menu();
	int in_put;
	do
	{
		printf("请输入 1 或 0 ：");
		scanf("%d", &in_put);
		switch (in_put)
		{
			
		case 1:game(); break;
		case 0:printf("成功退出\n"); break;
		default:printf("输入有误，请重新输入！"); break;

		}

	} while (in_put);
}

void game(void)
{
	srand((unsigned int)time(NULL));	//time 的头文件是 time.h
	char ret;

	char board[ROW][COL] = {0};		//这里用ROW和COL而不用具体数字是为了一个方便修改
	Initboard(board, ROW, COL);		//对数组进行初始化，先将数组的每个位置都置为空，再进行修改存值

	//DisplayBoard(board, ROW, COL);//打印数组

	//下面开始游戏，只有在用户输入0时才推出游戏
	while (1)
	{
		PlayerMove(board, ROW, COL);//玩家先行
		DisplayBoard(board, ROW, COL);
		printf("\n");

		ret=IsWin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}

		ComputerMove(board, ROW, COL);//电脑后行
		DisplayBoard(board, ROW, COL);
		printf("\n");
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}

	}
	if (ret == '*')
	{
		printf("玩家胜利！\n");
	}
	else if (ret == '#')
	{
		printf("电脑胜利！\n");
	}
	else if (ret == 'Q')
	{
		printf("达成平局！\n");
	}

	printf("\n");
	printf("\n");


}

void Initboard(char board[ROW][COL], int row,int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for ( j = 0; j < col; j++)
		{
			board[i][j] = ' ';//初始化为空
		}
	}

}

void DisplayBoard(char board[ROW][COL], int row, int col)
{
	/*
	打印的棋盘样式
	   |   |		可以把它大体上分为三个部分，小格上面都是三个空格，在这个空格中可以放置字符，即数组中的值
	---|---|---
	   |   |   
	---|---|---
	   |   |   
	   */
	/*
	比如第一个部分就是这样的
	   |   |   
	---|---|---
	*/

	int i, j;
	for (i = 0; i < row; i++)	//打印三行
	{
		for ( j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);	//打印的第一行中棋盘的小格的内容
			if (j < col - 1)	//在棋盘中只有两条竖线
			{
				printf("|");
			}
			
		}
		printf("\n");	//换行，打印的第一行完成

		//下面打印第一部分的第二行
		if (i < row - 1)	//在棋盘中只有两条横线
		{
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
				{
					printf("|");
				}

			}
			printf("\n");//换行，第一部分打印完毕
		}

	}

}

void PlayerMove(char board[ROW][COL], int row, int col)
{
	//玩家用*，电脑用#
	
	int x, y;
	printf("玩家行棋！\n");
	while (1)
	{
		printf("请输入您要落子的坐标：");
		scanf("%d%d", &x, &y);

		if (x >=1 && x <=row && y>=1 && y <=col)//从玩家出发，要从1开始
		{
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;//跳出while 循环，让电脑行棋
			}
			else
			{
				printf("该坐标已经被占用!");
			}

		}
		else
		{
			printf("该坐标非法!");
		}

	}

}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	printf("电脑行棋！\n");
	int x, y;
	/*rand 函数需要头文件<stdlib.h>,要保证每次产生的随机数都不同，就要借用srand，使用当前时间的毫秒数
	来作为种子数，产生随机数，srand写在game函数中 */
	
	//下面来判断产生的随机数坐标是否是被占用的，和上面一样,只是要确保电脑可以行棋，就用了循环
	while (1)
	{
		x = rand() % row;//调用随机函数来实现
		y = rand() % col;//通过对行和列取余运算，可以保证得到的随机值是在范围内的 

		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
	
	printf("\n");

}

int IsFull(char board[ROW][COL], int row, int col)
{
	int i, j;
	for ( i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;	//表示还没有满
			}
				
		}

	}
	return 1;	//表示已经满了
}

char IsWin(char board[ROW][COL], int row, int col)
{
	//返回四种游戏状态，以返回字符来表示结果
	//玩家胜利	'*'
	//电脑胜利	'#'
	//平局		'Q'
	//游戏继续	'C'

	int i, j;
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2]&&board[i][0]!=' ')
		{//行 字符相等且不为空
			return board[i][1];//直接返回该行相同的字符，以返回值来确定胜利者
		}
	}
	for (j = 0; j < col; j++)//列
	{
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
		{
			return board[0][j];
		}
	}

	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
	{	//主对角线
		return board[1][1];
	}

	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
	{
		return board[1][1];
	}

	if (1==IsFull(board,ROW,COL))
	{
		return 'Q';
	}

	return 'C';	//如果以上的条件都不符合，则继续游戏

}
