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
	printf("****** 1 .��ʼ ******\n");
	printf("****** 2 .�˳� ******\n");
	printf("*********************\n");
}

void input(void)
{
	menu();
	int in_put;
	do
	{
		printf("������ 1 �� 0 ��");
		scanf("%d", &in_put);
		switch (in_put)
		{
			
		case 1:game(); break;
		case 0:printf("�ɹ��˳�\n"); break;
		default:printf("�����������������룡"); break;

		}

	} while (in_put);
}

void game(void)
{
	srand((unsigned int)time(NULL));	//time ��ͷ�ļ��� time.h
	char ret;

	char board[ROW][COL] = {0};		//������ROW��COL�����þ���������Ϊ��һ�������޸�
	Initboard(board, ROW, COL);		//��������г�ʼ�����Ƚ������ÿ��λ�ö���Ϊ�գ��ٽ����޸Ĵ�ֵ

	//DisplayBoard(board, ROW, COL);//��ӡ����

	//���濪ʼ��Ϸ��ֻ�����û�����0ʱ���Ƴ���Ϸ
	while (1)
	{
		PlayerMove(board, ROW, COL);//�������
		DisplayBoard(board, ROW, COL);
		printf("\n");

		ret=IsWin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}

		ComputerMove(board, ROW, COL);//���Ժ���
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
		printf("���ʤ����\n");
	}
	else if (ret == '#')
	{
		printf("����ʤ����\n");
	}
	else if (ret == 'Q')
	{
		printf("���ƽ�֣�\n");
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
			board[i][j] = ' ';//��ʼ��Ϊ��
		}
	}

}

void DisplayBoard(char board[ROW][COL], int row, int col)
{
	/*
	��ӡ��������ʽ
	   |   |		���԰��������Ϸ�Ϊ�������֣�С�����涼�������ո�������ո��п��Է����ַ����������е�ֵ
	---|---|---
	   |   |   
	---|---|---
	   |   |   
	   */
	/*
	�����һ�����־���������
	   |   |   
	---|---|---
	*/

	int i, j;
	for (i = 0; i < row; i++)	//��ӡ����
	{
		for ( j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);	//��ӡ�ĵ�һ�������̵�С�������
			if (j < col - 1)	//��������ֻ����������
			{
				printf("|");
			}
			
		}
		printf("\n");	//���У���ӡ�ĵ�һ�����

		//�����ӡ��һ���ֵĵڶ���
		if (i < row - 1)	//��������ֻ����������
		{
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
				{
					printf("|");
				}

			}
			printf("\n");//���У���һ���ִ�ӡ���
		}

	}

}

void PlayerMove(char board[ROW][COL], int row, int col)
{
	//�����*��������#
	
	int x, y;
	printf("������壡\n");
	while (1)
	{
		printf("��������Ҫ���ӵ����꣺");
		scanf("%d%d", &x, &y);

		if (x >=1 && x <=row && y>=1 && y <=col)//����ҳ�����Ҫ��1��ʼ
		{
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;//����while ѭ�����õ�������
			}
			else
			{
				printf("�������Ѿ���ռ��!");
			}

		}
		else
		{
			printf("������Ƿ�!");
		}

	}

}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	printf("�������壡\n");
	int x, y;
	/*rand ������Ҫͷ�ļ�<stdlib.h>,Ҫ��֤ÿ�β��������������ͬ����Ҫ����srand��ʹ�õ�ǰʱ��ĺ�����
	����Ϊ�������������������srandд��game������ */
	
	//�������жϲ���������������Ƿ��Ǳ�ռ�õģ�������һ��,ֻ��Ҫȷ�����Կ������壬������ѭ��
	while (1)
	{
		x = rand() % row;//�������������ʵ��
		y = rand() % col;//ͨ�����к���ȡ�����㣬���Ա�֤�õ������ֵ���ڷ�Χ�ڵ� 

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
				return 0;	//��ʾ��û����
			}
				
		}

	}
	return 1;	//��ʾ�Ѿ�����
}

char IsWin(char board[ROW][COL], int row, int col)
{
	//����������Ϸ״̬���Է����ַ�����ʾ���
	//���ʤ��	'*'
	//����ʤ��	'#'
	//ƽ��		'Q'
	//��Ϸ����	'C'

	int i, j;
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2]&&board[i][0]!=' ')
		{//�� �ַ�����Ҳ�Ϊ��
			return board[i][1];//ֱ�ӷ��ظ�����ͬ���ַ����Է���ֵ��ȷ��ʤ����
		}
	}
	for (j = 0; j < col; j++)//��
	{
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
		{
			return board[0][j];
		}
	}

	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
	{	//���Խ���
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

	return 'C';	//������ϵ������������ϣ��������Ϸ

}
