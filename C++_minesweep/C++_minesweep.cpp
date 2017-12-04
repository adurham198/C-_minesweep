//Project Minesweeper
//Authors: Andrew, Anton, Lucas
#include "stdafx.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>
#include <time.h>

using namespace std;
void displaygamescore();
int again(int);
void welcomemessage();
void reveal(int, int);
void createmines();
void admin_grid();
void cell_number(int, int);
void buildgrid();
void open_cell();
void game();
void revealgrid(char[][10]);

char table[10][10];
char minepositions[10][10];
int score = 0;
int flag_counter = 0;
int mines_flagged_counter = 0;
bool end_game_lose = false;
time_t time_since = time(0);
time_t game_time;




void welcomemessage()
{
	cout << "WELCOME TO MINESWEEPER " << endl;
	cout << "***********************************" << endl;
	cout << "HERE ARE THE RULES " << endl;
	cout << "***********************************" << endl;
	cout << "1. Enter 'o' , then enter (x,y) coordinates for a row and column to reveal that cell." << endl;
	cout << "2. Enter 'f' ,then enter (x,y) coordinates for a row and a column to place flag " << endl;
	cout << "or remove already existing flag on that cell." << endl;
	cout << "3. Enter 'a' if you wish to use the administrator view." << endl;
	cout << endl;

}
void cell_number(int rows, int cols)
{
	if (rows >= 0 && rows < 10 && cols >= 0 && cols < 10 && minepositions[rows][cols] != 'X')
	{
		minepositions[rows][cols]++;
	}
}

void createmines()
{
	int minesLeft = 20;
	srand(time(NULL));
	for (int rows = 0; rows < 10; rows++)
	{
		for (int cols = 0; cols < 10; cols++)
			minepositions[rows][cols] = '0';
	}
	int rows = 0;
	int cols = 0;
	for (int counter = 0; counter < minesLeft; counter++)
	{
		int rows = rand() % 10;
		int cols = rand() % 10;
		if (minepositions[rows][cols] != 'X')
		{
			minepositions[rows][cols] = 'X';
			cell_number(rows - 1, cols);
			cell_number(rows + 1, cols);
			cell_number(rows, cols - 1);
			cell_number(rows, cols + 1);
			cell_number(rows - 1, cols - 1);
			cell_number(rows - 1, cols + 1);
			cell_number(rows + 1, cols - 1);
			cell_number(rows + 1, cols + 1);
		}
		else {
			counter--;
		}
	}

}

void buildgrid()
{
	for (int rows = 0; rows < 10; rows++)
	{
		for (int cols = 0; cols < 10; cols++)
		{
			table[rows][cols] = '*';
		}
	}
}
//Anton: The function buildgrid is making each of the row and column values asterisks here to simulate the user viewing a board
//with blank spaces. It works using nested for-loops to run through our entire grid's array values.
void revealgrid(char arr[10][10])
{
	cout << "    ";
	for (int rows = 0; rows < 10; rows++)

		cout << setw(3) << rows;

	cout << endl << "  ";

	for (int rows = 0; rows < 32; rows++)

		cout << "_";
	cout << endl;

	for (int rows = 0; rows < 10; rows++)
	{
		cout << setw(3) << rows << "|";
		for (int cols = 0; cols < 10; cols++)
			cout << setw(3) << arr[rows][cols];
		cout << endl;
	}

}

void admin_grid()
{
	for (int rows = 0; rows < 10; rows++)
	{
		for (int cols = 0; cols < 10; cols++)
		{
			table[rows][cols] = minepositions[rows][cols];
		}
	}
}

void open_cell()
{
	int rows;
	int cols;


	cin >> rows >> cols;
	if (rows<0 || rows >10 || cols <0 || cols>10)
		while (rows<0 || rows>9 || cols<0 || cols>9);
	{
		if (minepositions[rows][cols] == 'X')
		{
			table[rows][cols] = 'X';
			end_game_lose = true;

			for (int rows = 0; rows < 10; rows++)
			{
				for (int cols = 0; cols < 10; cols++)
					if (minepositions[rows][cols] == 'X')
						table[rows][cols] = 'X';
			}
		}

		else
		{
			score++;
			reveal(rows, cols);
		}
		//Anton:These if statements and for-loop check to see if there is a mine at the position the user opened. If there is a bomb, 
		//the game ends. If there is no mine, it calls the reveal function and increases the user's score by one.
	}
}

void place_or_remove_flag()
{
	int rows = 0;
	int cols = 0;
	cin >> rows >> cols;
	while (rows<0 || rows>9 || cols<0 || cols>9);
	{
		if (table[rows][cols] == '*')
		{
			table[rows][cols] = 'F';
			flag_counter++;

			if (minepositions[rows][cols] == 'X')
				mines_flagged_counter++;
		}

		else if (table[rows][cols] == 'F')
		{
			table[rows][cols] = '*';
			flag_counter--;
			if (minepositions[rows][cols] == 'X')
				mines_flagged_counter--;
		}
	}
}

void input_symbol()
{
	char symbol;
	cin >> symbol;
	while (symbol != 'o' && symbol != 'f' && symbol != 'a')
	{
		cout << "Invalid input, try again. " << endl;
		cin >> symbol;
	}
	if (symbol == 'o' || symbol == 'f' || symbol == 'a')
	{
		switch (symbol) {
		case 'o': open_cell(); break;
		case 'f': place_or_remove_flag(); break;
		case 'a': admin_grid(); break;
		default: input_symbol();
		}
	}
}

void reveal(int rows, int cols)
{
	if (table[rows][cols] == '*'&& minepositions[rows][cols] != 'X'&&rows >= 0 && rows<10 && cols >= 0 && cols<10)
	{
		table[rows][cols] = minepositions[rows][cols];

		if (minepositions[rows][cols] == '0')
		{
			reveal(rows, cols - 1);
			reveal(rows, cols + 1);
			reveal(rows - 1, cols - 1);
			reveal(rows + 1, cols - 1);
			reveal(rows + 1, cols + 1);
			reveal(rows - 1, cols + 1);
			reveal(rows - 1, cols);
			reveal(rows + 1, cols);
		}
		//Anton: This if statement is really important, because it changes cells around the user selected cell 
		//based on how many mines there were around it.
	}
}

bool end_game_win_check()
{
	if (flag_counter == 10 && mines_flagged_counter == 10)
		return 1;
	else
		return 0;
}
int again(int replay)
{
	cout << " If you would like to play again, please enter 0. If you do not want to, enter 1. " << endl;
	cin >> replay;
	return replay;
}

void game()
{
	buildgrid();
	createmines();

	while (!end_game_lose && !end_game_win_check())
	{
		game_time = time(0);
		revealgrid(table);
		cout << endl << "Flags used:" << flag_counter << endl;
		cout << "Time played:" << game_time - time_since << " seconds" << endl;
		input_symbol();
	}

	if (end_game_lose)
	{
		revealgrid(table);
		cout << endl << "GAME OVER" << endl;
		admin_grid();
	}

	if (end_game_win_check())
	{
		cout << "Time to complete:" << game_time - time_since << endl;
		cout << endl << "YOU WIN!" << endl;
	}
}
void displaygamescore()
{
	cout << "This was your score: " << score << endl;
}
int main()
{
	int replay = 0;
	if (replay == 0)
	{
		welcomemessage();
		game();
		displaygamescore();
		again(replay);
	}
	else {
		cout << " Thanks for playing!" << endl;
	}
	system("Pause");
	return 0;
}
