/*Valentine Gundorov
minesweeper game
and you can use a cheat for the advancement of the game by using (-1) and then the amount of cells that you want to open
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 40

int gameboard[SIZE][SIZE];
int isopenboard[SIZE][SIZE];
time_t t;

void gameBoardfx(int, int, int ,int, char);
void fillboard(int, int);
void printfinalboard(int, int);
int isBoardCleared(int, int);
void cheat(int, int, int);
void openSpace(int, int, int ,int );

void main()
{
	int a, b;
	int sizeNumber, exit = 1, rows=0, columns=0;
	while (exit)
	{
		printf("Welcome to Minesweeper!\n\n");
		printf("Please choose one of the following options \n\n");
		printf("1 - for size 8X8\n\n");
		printf("2 - for size 12X12\n\n");
		printf("3 - for size 15X15\n\n");
		printf("4 - for custom size\n\n");
		printf("0 - exit\n\n");
		scanf("%d", &sizeNumber);

		switch (sizeNumber)
		{

		case 1:
			rows = 8;
			columns = 8;
			exit = 0;
			gameBoardfx(rows, columns, -1,-1, -1);
			fillboard(rows, columns);
			break;
		case 2:
			rows = 12;
			columns = 12;
			exit = 0;
			gameBoardfx(rows, columns, -1, -1, -1);
			fillboard(rows, columns);
			break;
		case 3:
			rows = 15;
			columns = 15;
			gameBoardfx(rows, columns, -1, -1, -1);
			fillboard(rows, columns);
			exit = 0;
			break;
		case 4:
			printf("Please enter the size of the board(Lines <= 22 and Cols <= 40) :\n");
			scanf("%d%d",&a,&b);
			rows = a;
			columns = b;
			if (rows > 22 || columns > 40 || rows < 0 || columns <0)
			{
				printf("wrong\n");
				continue;
			}
			gameBoardfx(rows, columns,-1 ,-1, -1);
			fillboard(rows, columns);
			exit = 0;
			break;
		default:
			break;
		}
	}

	while (1)
	{
		int row, col ;
		char flag;
		printf("Please enter your move, row and column : \n");
		scanf("%d%d", &row, &col);
		if (row != -1)
		{
			scanf("%c", &flag);
			if (flag != 'f' && flag != 'o' && flag != 'F' && flag != 'O')
			{
				printf("wrong\n");
				continue;
			}
		}
	
		if (row==-1)
		{
			 cheat(col, rows, columns);
			 gameBoardfx(rows, columns, row ,col, flag);
			 if (col >= rows * columns)
			 {
				 printf("You won!! congratulations! CHAMPION!\n");
				 break;
			 }
			 continue;
		}

		if ((row < 0 || row >= rows || col<0 || col >= columns) || (isopenboard[row][col] == 1))
		{
			printf("Invalid move, please enter valid choice!\n");
			continue;
		}
		if (flag == 'f' || flag == 'F')
		{
			isopenboard[row][col] = -1;
		}
		else
			isopenboard[row][col] = 1;
		gameBoardfx(rows, columns,row ,col, flag);
		if (gameboard[row][col] == -1)
		{
			printf("You've hit a bomb! Game over!\n");
			printfinalboard(rows, columns);
			break;
		}
		else if(isBoardCleared(rows, columns) == 1)
		{
			printf("You won!! congratulations! CHAMPION!\n");
			break;

		}
	}
}

void gameBoardfx(int rows, int columns, int row , int col ,char flag)
{
	int i, j;
	int num = 0;
	if (row != -1 && isopenboard[row][col] == 1 && gameboard[row][col] == 0)
	{
		isopenboard[row][col] = 0;
		openSpace(row, col, rows, columns);
	}
	printf("    ");
	for (i = 0; i < columns; i++)
	{
		if (i < 9)
			printf(" %d ", i);
		else
		printf(" %d", i);
	}
	printf("\n\n");
	/*for (i = 0; i < size; i++)
	{
		printf("_");
	}
	printf("\n");*/

	for (i = 0; i < rows; i++)
	{
			if(i<=9)
			printf("  %d ", i);
			else
				printf(" %d ", i);
	
		for (j = 0; j < columns; j++)
		{
			if(isopenboard[i][j]==0)
				printf(" X ");
			else if (isopenboard[i][j] == -1)
			{
				printf(" F ");
			}
			else 
			{
				if (gameboard[i][j] == -1)
				{
					printf(" * ");
				}
				else if (gameboard[i][j] == 0)
				{
					printf("   ");
				}
				else 
				{
					printf(" %d ", gameboard[i][j]);
				}
			}
			
		}
		printf("\n");
	}


	/*for (i = 0; i < 36; i++)
	{
		printf("_");
	}
	printf("\n");*/

}

void fillboard(int rows,  int columns)
{
	int row, col, bombs;
	srand(time(NULL));
	bombs = sqrt(rows * columns);
	for (int k = 0; k<bombs; k++)
	{
		row = rand() % rows;
		col = rand() % columns;
		if (gameboard[row][col] != -1)
		{
			gameboard[row][col] = -1;
		}
		else
			k--;
	}
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++)
		{
			if (gameboard[i][j] != -1) 
			{
				int bombcounter = 0;
				for (int g = i - 1; g < i + 2; g++)
				{
					for (int h = j - 1; h < j + 2; h++) 
					{
						if ((g >= 0 && g < rows) && (h >= 0 && h < columns)) 
						{
							if (gameboard[g][h] == -1) 
							{
								bombcounter++;
							}
						}
					}
				}
				gameboard[i][j] = bombcounter;
			}
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			isopenboard[i][j] = 0;
	}
}

void printfinalboard(int rows, int columns)
{
	for (int i = 0; i < 8; i++)
	{
		printf(" %d ", i);

	}
	printf("\n");
	/*for (int i = 0; i < 36; i++)
	{
		printf("_");
	}*/
	printf("\n");


	for (int i = 0; i < rows ; i++)
	{
		printf(" %d ", i);
		for(int j = 0; j < columns; j++)
		{
			if (gameboard[i][j] == -1)
			{
				printf(" * ");
			}
			else if (gameboard[i][j] == 0)
			{
				printf("   ");
			}
			else {
				printf(" %d ", gameboard[i][j]);
			}
		
		}
		printf("\n");
	}
}

int isBoardCleared(int rows, int columns) 
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++){
			if (isopenboard[i][j] == 0 && gameboard[i][j] != -1) {
				return 0;
			}
		}
	}
	return 1;
}

void cheat(int col, int rows, int columns)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (isopenboard[i][j] != 1 && gameboard[i][j] != -1)
			{
				isopenboard[i][j] = 1;
				col--;
				if (col == 0)
					return;
			}				
		}
	}		
}
void openSpace(int row, int col, int rows ,int columns)
{
	if (row < 0 || row >= rows || col<0 || col >= columns || isopenboard[row][col] == 1)
		return;

	isopenboard[row][col] = 1;

	if (gameboard[row][col] > 0)	
		return;

	openSpace(row-1, col-1, rows, columns);
	openSpace(row-1, col, rows, columns);
	openSpace(row-1, col+1, rows, columns);
	openSpace(row, col-1, rows, columns);
	openSpace(row, col+1, rows, columns);
	openSpace(row+1, col-1, rows, columns);
	openSpace(row+1, col, rows, columns);
	openSpace(row+1, col+1, rows, columns);	
}
