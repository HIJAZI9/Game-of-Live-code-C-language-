#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include<windows.h>


int ROWS = 20, COLS = 20;
void print_board(char** board);
void freeMatrix(void** board);
void copyMatrix(char** board, int ROWS_1, int COLS_1, char** temp, int ROWS_2, int COLS_2);
int count_neighbors(char** board, int x, int y);
void update_board(char** board);


int count_first_corner(int** board)
{
	return board[0][1] + board[1][1] + board[1][0];
}

int count_row_below(int** board, int x, int y)
{
	return board[x + 1][y - 1] + board[x + 1][y] + board[x + 1][y + 1];
}

int count_second_corner(int** board)
{
	return board[0][COLS - 2] + board[1][COLS - 2] + board[1][COLS - 1];
}
int count_third_corner(int** board)
{
	return board[ROWS - 1][1] + board[ROWS - 2][0] + board[ROWS - 2][1];
}
int count_fourth_corner(int** board)
{
	return board[ROWS - 1][COLS - 2] + board[ROWS - 2][COLS - 1] + board[ROWS - 2][COLS - 2];
}

int count_upper_row(int** board, int x, int y)
{
	return board[x - 1][y - 1] + board[x - 1][y] + board[x - 1][y + 1];
}

int count_right_cols(int** board, int x, int y)
{
	return board[x - 1][y + 1] + board[x][y + 1] + board[x + 1][y + 1];
}
int count_left_cols(int** board, int x, int y)
{
	return board[x - 1][y - 1] + board[x][y - 1] + board[x + 1][y - 1];
}
int count_middle(int** board, int x, int y)
{
	int row_below = count_row_below(board, x, y);
	int row_upper = count_upper_row(board, x, y);
	return row_below + row_upper + board[x][y - 1] + board[x][y + 1];
}

void open_File(char** board);
int menu1();
int menu2();
int menu3();
int menu4();
int menu5();
int menu6();
void saveGame(char** board, const char* fileName);
void loadSavedGame(char** board, const char* fileName);
void increaseIntensity(char** board, int oldI, int newI);
void decreaseIntensity(char** board, int oldI, int newI);
void updateIntensity(char** board, int newI);
void settings(char** board, int* newROWS, int* newCOLS);
void startGame(char** board);
void print_board_for_map(char** board);


int main()
{
	time_t t;
	srand((unsigned)time(&t));
	char** board = NULL;
	board = (char**)calloc(ROWS, sizeof(char*));
	for (int i = 0; i < ROWS; i++)
	{
		board[i] = (char*)calloc(COLS, sizeof(char));
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			board[i][j] = ' ';
		}
	}
	open_File(board);

	int x = -1, y = -1;
	char ch;
	int a = 20, b = 20;
	int* newHeight = &a;
	int* newWeight = &b;
	int** temp = NULL;
	while (1)
	{
		switch (menu1())
		{
		case 1:
			system("cls");
			startGame(board);
			break;
		case 2:
			system("cls");
			switch (menu5())
			{
			case 1:
				loadSavedGame(board, "one.txt");
				break;
			case 2:
				loadSavedGame(board, "two.txt");
				break;
			case 3:
				loadSavedGame(board, "three.txt");
				break;
			}
			system("cls");
			startGame(board);
			break;
		case 3:

			while (1)
			{

				system("cls");
				print_board_for_map(board);
				printf("Enter the Coordinate you wanna edit: ");
				scanf("%d", &x);
				getchar();
				scanf("%d", &y);
				getchar();
				printf("\nEnter character(space for nothing/* for living cell): ");
				scanf("%c", &ch);
				if (ch == '*')
					board[x][y] = '*';
				else
					board[x][y] = ' ';
				while (getchar() != '\n');
				printf("Do you want edit again(y/n): ");
				scanf("%c", &ch);
				if (ch == 'n')
				{
					system("cls");
					switch (menu4())
					{
					case 1:
						saveGame(board, "one.txt");
						break;
					case 2:
						saveGame(board, "two.txt");
						break;
					case 3:
						saveGame(board, "three.txt");
						break;
					}
					system("cls");
					break;
				}

				getchar();
			}
			break;

		case 4:
			system("cls");

			settings(board, newHeight, newWeight);
			temp = board;
			board = NULL;
			board = (char**)calloc(*newHeight, sizeof(char*));
			for (int i = 0; i < *newHeight; i++)
			{
				board[i] = (char*)calloc(*newWeight, sizeof(char));
			}
			for (int i = 0; i < *newHeight; i++)
			{
				for (int j = 0; j < *newWeight; j++)
				{
					board[i][j] = ' ';
				}
			}
			copyMatrix(board, ROWS, COLS, temp, *newHeight, *newWeight);
			freeMatrix(temp);
			ROWS = *newHeight;
			COLS = *newWeight;
			system("cls");
			break;
		case 5:
			system("cls");
			exit(0);
			break;
		}


	}


}
void print_board(char** board)
{
	/* initialize matrix */
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
			printf("%c", board[i][j]);
		putchar('\n');
	}
}
void freeMatrix(void** board)
{
	for (int i = 0; i < ROWS; i++)
	{
		free(board[i]);
		board[i] = NULL;
	}
	free(board);
	board = NULL;
}
void copyMatrix(char** board, int ROWS_1, int COLS_1, char** temp, int ROWS_2, int COLS_2)
{
	int ROWS = ROWS_1 > ROWS_2 ? ROWS_2 : ROWS_1;
	int COLS = COLS_1 > COLS_2 ? COLS_2 : COLS_1;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			board[i][j] = temp[i][j];
		}
	}

}
int count_neighbors(char** board, int x, int y)
{

	int neighbors = 0;
	int** ones_board = NULL;
	ones_board = malloc(ROWS * sizeof(int*));
	for (int i = 0; i < ROWS; i++)
	{
		ones_board[i] = malloc(COLS * sizeof(int));
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			ones_board[i][j] = 0;
		}
	}


	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (board[i][j] == '*')
				ones_board[i][j] = 1;
			else
				ones_board[i][j] = 0;
		}
	}

	if (x == 0)
	{
		if (y == 0)
		{
			neighbors = count_first_corner(ones_board);
		}
		else if (y == COLS - 1)
		{
			neighbors = count_second_corner(ones_board);
		}
		else
		{
			neighbors = count_row_below(ones_board, x, y);
		}

	}
	else if (x == ROWS - 1)
	{
		if (y == 0)
		{
			neighbors = count_third_corner(ones_board);
		}
		else if (y == COLS - 1)
		{
			neighbors = count_fourth_corner(ones_board);
		}
		else
		{
			neighbors = count_upper_row(ones_board, x, y);
		}
	}
	else
	{
		if (y == 0)
		{
			neighbors = count_right_cols(ones_board, x, y);
		}
		else if (y == COLS - 1)
		{
			neighbors = count_left_cols(ones_board, x, y);
		}
		else
		{
			neighbors = count_middle(ones_board, x, y);
		}
	}
	freeMatrix(ones_board);
	return neighbors;
}

void update_board(char** board)
{

	char** result_board = NULL;
	result_board = (char**)calloc(ROWS, sizeof(char*));
	for (int i = 0; i < ROWS; i++)
	{
		result_board[i] = (char*)calloc(COLS, sizeof(char));
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			result_board[i][j] = ' ';
		}
	}
	int neighbors = 0;

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
		{
			result_board[i][j] = board[i][j];
		}


	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			neighbors = count_neighbors(board, i, j);
			if (board[i][j] == '*')
			{
				if (neighbors < 2 || neighbors > 3)
				{
					result_board[i][j] = ' ';
				}
			}
			else if (board[i][j] == ' ')
			{
				if (neighbors == 3)
				{
					result_board[i][j] = '*';
				}
			}
		}
	}


	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			board[i][j] = result_board[i][j];
		}
	}
	freeMatrix(result_board, ROWS, COLS);
}
void open_File(char** board)
{
	FILE* configuration1 = NULL;
	configuration1 = fopen("configuration1.txt", "r");
	char ch;
	if (configuration1 != NULL)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int z = 0; z < COLS; z++)
			{
				fscanf(configuration1, "%c", &ch);
				if (ch == '*')
					board[i][z] = ch;
				else
					board[i][z] = ' ';
			}

		}
		fclose(configuration1);
	}
	else
	{
		printf("we can not open this file");
	}
}
int menu1()
{
	int z;
	printf("\n1-start game \n");
	printf("2-load game \n");
	printf("3-Map Editor\n");
	printf("4-Settings\n");
	printf("5-exit\n  ");
	printf("choice>>");
	scanf("%d", &z);
	return z;
}
int menu2()
{
	printf("1-Step By Step\n");
	printf("2-Animation\n");
	printf("3-Back\n");
	printf("choice>>");

	int i;
	scanf("%d", &i);
	return i;
}
int menu3()
{
	printf("1-save Game\n");
	printf("2-back\n");
	printf("choice>>");
	int i;
	scanf("%d", &i);
	return i;

}
int menu4()
{
	printf("Which file would you save your game ?\n");
	printf("1-EmptyFile1\n");
	printf("2-EmptyFile2\n");
	printf("3-EmptyFile3\n");
	printf("choice>>");
	int i;
	scanf("%d", &i);
	return i;

}
int menu5()
{
	printf("Select file in which you saved your game?\n");
	printf("1-File1\n");
	printf("2-File2\n");
	printf("3-File3\n");
	printf("choice>>");
	int i;
	scanf("%d", &i);
	return i;

}
int menu6() {
	printf("1- height\n");
	printf("2- Width\n");
	printf("3- Intensity\n");
	printf("4- Back\n");
	printf("choice>>");
	int i;
	scanf("%d", &i);
	return i;

}
void saveGame(char** board, const char* fileName)
{

	FILE* file = NULL;
	file = fopen(fileName, "w");

	if (file != NULL)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int z = 0; z < COLS; z++)
			{
				fputc(board[i][z], file);
			}

		}
		fclose(file);
	}
	else
	{
		printf("we can not open this file");
	}
}
void loadSavedGame(char** board, const char* fileName)
{
	FILE* file = NULL;
	file = fopen(fileName, "r");

	if (file != NULL)
	{

		for (int i = 0; i < ROWS; i++)
		{
			for (int z = 0; z < COLS; z++)
			{
				fscanf(file, "%c", &board[i][z]);
			}

		}
		fclose(file);
	}
	else
	{
		printf("we can not open this file");
	}
}
void increaseIntensity(char** board, int oldI, int newI)
{

	int a = rand() % ROWS;
	int b = rand() % COLS;
	while (oldI <= newI)
	{
		while (1)
		{
			if (board[a][b] == ' ')
			{
				board[a][b] = '*';
				oldI++;
				break;
			}
			a = rand() % ROWS;
			b = rand() % COLS;
		}

	}
}
void decreaseIntensity(char** board, int oldI, int newI)
{
	int a = rand() % ROWS;
	int b = rand() % COLS;
	while (oldI <= newI)
	{
		while (1)
		{
			if (board[a][b] == '*')
			{
				board[a][b] = ' ';
				oldI--;
				break;
			}
			a = rand() % ROWS;
			b = rand() % COLS;
		}

	}
}
void updateIntensity(char** board, int newI)
{
	int count = 0;
	int newCount = newI;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (board[i][j] == '*')
				count++;
		}
	}
	if (count == newI)
		return;
	if (count > newI)
		decreaseIntensity(board, count, newI);
	else
		increaseIntensity(board, count, newI);
}
void settings(char** board, int* newROWS, int* newCOLS) {
	int u;
	char** temp = NULL;

	switch (menu6())
	{
	case 1:
		printf("what height do you want?\n");
		scanf("%d", &u);
		*newROWS = u;
		break;
	case 2:
		printf("what weight do you want?\n");
		scanf("%d", &u);
		*newCOLS = u;
		break;
	case 3:
		printf("what intensity do you want?\n");
		scanf("%d", &u);
		updateIntensity(board, u);
		system("cls");
		break;
	default:
		break;
	}
}
void startGame(char** board)
{
	int step1, endd, step, end;
	switch (menu2())
	{
	case 1:
		printf("How many steps should be animated at most?");
		step;
		scanf("%d", &step);
		end = 0;
		step = step - 1;
		system("cls");
		for (int i = 0; end == 0; i++)
		{
			print_board(board, ROWS, COLS);
			update_board(board, ROWS, COLS);
			printf("ITERATION NUMBER %d\n", i + 1);
			if (end != 1) {
				printf("1- next Generation\n");
				printf("choice>>");
			}
			int u;    scanf("%d", &u);
			if (i != step)  system("cls");

			if (i == step)
			{
				end = 1;

			}


		}


		switch (menu3())
		{
		case 1:
			system("cls");
			switch (menu4())
			{
			case 1:
				saveGame(board, "one.txt");
				break;
			case 2:
				saveGame(board, "two.txt");
				break;
			case 3:
				saveGame(board, "three.txt");
				break;
			}
			system("cls");
			break;
		case 2:
			system("cls");

			break;
		}
		break;

	case 2:

		// system("cls");
		printf("How many steps should be animated at most?");
		step1;
		scanf("%d", &step1);
		endd = 0;
		step1 = step1 - 1;
		system("cls");
		for (int i = 0; endd == 0; i++)
		{
			print_board(board);
			update_board(board);
			//  printf("ITERATION NUMBER %d\n", i+1);
			Sleep(1);

			if (i != step1)  system("cls");

			if (i == step1)
			{
				endd = 1;

			}


		}


		switch (menu3())
		{
		case 1:
			system("cls");
			switch (menu4())
			{
			case 1:
				saveGame(board, "one.txt");
				break;
			case 2:
				saveGame(board, "two.txt");
				break;
			case 3:
				saveGame(board, "three.txt");
				break;
			}
			system("cls");
			break;
		case 2:
			system("cls");

			break;
		}
		break;

	case 3:

		system("cls");
		break;
	}




}
void print_board_for_map(char** board)
{
	int row, col;
	//puts("     0   1   2   3   4   5   6   7   8   9  10  11  12  13   14  15  16  17  18  19\n");
	puts("  ");
	for (int i = 0; i < COLS; i++)
	{
		printf("   %d", i);
	}
	printf("\n");
	//puts("-----------------------------------------------------------------------------------------");
	for (int i = 0; i < COLS; i++)
	{
		if (i % 2 == 0)
			printf("-----");
		else
			printf("----");
	}
	printf("\n");
	for (row = 0; row < ROWS; row++)
	{
		printf("%d  ", row);
		for (col = 0; col < COLS; col++)
		{
			printf("| %c ", board[row][col]);
		}
		puts("|\n");
	}
	//puts("-----------------------------------------------------------------------------------------");
	for (int i = 0; i < COLS; i++)
	{
		if (i % 2 == 0)
			printf("-----");
		else
			printf("----");
	}
	printf("\n");
}

