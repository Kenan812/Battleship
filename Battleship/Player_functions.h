#pragma once

#include <iostream>
#include <time.h>
#include <Windows.h>
#include <vector>

using namespace std;

void InitializePlayerBoard(int** Board);
void PrintPlayerBoard(int** Board);
void ReplaceHitByDead(int** Board);
bool PlayerHits(int** player_1_board, int** player_2_board, int& player_2_ship_count);
bool IsDead(int** Board, int type_of_ship);  // Checks if there is a dead ship on the board. Returns true if there is
void SetNotPlacableZone(int** Board, int start_row, int start_column, int end_row, int end_column, int horizontal_or_vertical);
void PrintExampleOfShipPlacing();
void PrintExampleOfShipPlacingForOneLengthShip();
void PrintBoards(int** player_1_board, int** player_2_board);

		
			/*  Main Functions   */

void InitializePlayerBoard(int** Board)
{
	system("cls");

	PrintExampleOfShipPlacing();

	PrintPlayerBoard(Board);

	int start_pos_row, end_pos_row;
	int start_pos_column, end_pos_column;
	int horizontal_or_vertical;  // horizontal-0/vertical-1

	
	bool three_length_ship;
	bool two_length_ship;
	bool one_length_ship;


	// 4-square-length-ship
	// indicates as 4
	cout << "\n\nPlace 4-square-length ship\n";

	cout << "Enter start and end positions: ";
	cin >> start_pos_row >> start_pos_column >> end_pos_row >> end_pos_column;  // accepts from 1-10



	if (start_pos_row == end_pos_row)
	{
		horizontal_or_vertical = 0;
		for (int i = start_pos_column - 1; i < end_pos_column; i++)
			Board[start_pos_row - 1][i] = 4;
	}

	else if (start_pos_column == end_pos_column)
	{
		horizontal_or_vertical = 1;
		for (int i = start_pos_row - 1; i < end_pos_row; i++)
			Board[i][start_pos_column - 1] = 4;
	}


	SetNotPlacableZone(Board, start_pos_row - 1, start_pos_column - 1, end_pos_row - 1, end_pos_column - 1, horizontal_or_vertical);



	// 3-square-length-ship
	// indicates as 3
	
	for (int i = 0; i < 2; i++)
	{
		system("cls");

		PrintExampleOfShipPlacing();

		PrintPlayerBoard(Board);

		three_length_ship = false;
		
		cout << "\n\nPlace 3-square-length ship\n";


		while (!three_length_ship)
		{

			cout << "Enter start and end positions: ";
			cin >> start_pos_row >> start_pos_column >> end_pos_row >> end_pos_column;

			
			if (start_pos_row == end_pos_row)
			{
				if (Board[start_pos_row-1][start_pos_column-1] == 0 && Board[start_pos_row-1][start_pos_column] == 0 && Board[start_pos_row - 1][start_pos_column + 1] == 0)
				{
					for (int i = start_pos_column - 1; i < end_pos_column; i++)
						Board[start_pos_row - 1][i] = 3;

					three_length_ship = true;

					SetNotPlacableZone(Board, start_pos_row-1, start_pos_column-1, end_pos_row-1, end_pos_column-1, 0);
				}

				else 
				{
					cout << "You can not place ship here" << endl << endl;
					Sleep(1000);
					system("cls");
					PrintExampleOfShipPlacing();
					PrintPlayerBoard(Board);
				}
	
			}


			else if (start_pos_column == end_pos_column) 
			{
				if (Board[start_pos_row-1][start_pos_column-1] == 0 && Board[start_pos_row][start_pos_column - 1] == 0 && Board[start_pos_row + 1][start_pos_column - 1] == 0)
				{
					for (int i = start_pos_row - 1; i < end_pos_row; i++)
						Board[i][start_pos_column - 1] = 3;

					three_length_ship = true;

					SetNotPlacableZone(Board, start_pos_row - 1, start_pos_column - 1, end_pos_row - 1, end_pos_column - 1, 1);

				}

				else 
				{
					cout << "You can not place ship here" << endl << endl;
					Sleep(1000);
					system("cls");
					PrintExampleOfShipPlacing();
					PrintPlayerBoard(Board);
				}


			}
		}

	}
	


	// 2-square-length-ship
	// indicates as 2
	
	for (int i = 0; i < 3; i++)
	{
		system("cls");
		PrintExampleOfShipPlacing();
		PrintPlayerBoard(Board);

		two_length_ship = false;

		cout << "\n\nPlace 2-square-length ship\n";

		while (!two_length_ship)
		{


			cout << "Enter start and end positions: ";
			cin >> start_pos_row >> start_pos_column >> end_pos_row >> end_pos_column;

			if (Board[start_pos_row - 1][start_pos_column - 1] == 0 && Board[end_pos_row - 1][end_pos_column - 1] == 0) 
			{
				Board[start_pos_row - 1][start_pos_column - 1] = 2;
				Board[end_pos_row - 1][end_pos_column - 1] = 2;

				two_length_ship = true;

				if (start_pos_row == end_pos_row)
					horizontal_or_vertical = 0;
				else 
					horizontal_or_vertical = 1;

				cout << horizontal_or_vertical << endl;
				cout << start_pos_row << " " << start_pos_column << endl;
				cout << end_pos_row << " " << end_pos_column << endl;

				SetNotPlacableZone(Board, start_pos_row - 1, start_pos_column - 1, end_pos_row - 1, end_pos_column - 1, horizontal_or_vertical);

			}
			
			else 
			{
				cout << "You can not place ship here" << endl << endl;
				Sleep(1000);
				system("cls");
				PrintExampleOfShipPlacing();
				PrintPlayerBoard(Board);
			}

		}


	}
	

	// 1-square-length-ship
	// indicates as 1
	for (int i = 0; i < 4; i++)
	{
		system("cls");
		PrintExampleOfShipPlacingForOneLengthShip();
		PrintPlayerBoard(Board);

		one_length_ship = false;

		cout << "\n\nPlace 1-square-length ship\n";


		while (!one_length_ship)
		{
			cout << "Enter position: ";
			cin >> start_pos_row >> start_pos_column;

			if (Board[start_pos_row - 1][start_pos_column - 1] == 0) 
			{
				Board[start_pos_row - 1][start_pos_column - 1] = 1;
				
				one_length_ship = true;

				SetNotPlacableZone(Board, start_pos_row - 1, start_pos_column - 1, start_pos_row - 1, start_pos_column - 1, 0);
			}

			else
			{
				cout << "You can not place ship here" << endl << endl;
				Sleep(1000);
				system("cls");
				PrintExampleOfShipPlacingForOneLengthShip();
				PrintPlayerBoard(Board);
			}

		}

	}


}


// subtracts 1 from player_2_ship_count when needed
bool PlayerHits(int** player_1_board, int** player_2_board, int& player_2_ship_count)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	PrintBoards(player_1_board, player_2_board);

	int row;
	int column;


	// player enters numbers from 1 to 10
	// program transfers to 0-9

	cout << "Enter '-1' to exit the game." << endl;
	cout << "Example of hit: " << endl;
	cout << "    2\t  3" << endl;
	cout << "    ^\t  ^" << endl;

	cout << "   Row\tColumn" << endl;

	cout << "Attack a position: ";
	cin >> row;
	if (row == -1)
		exit(1);
	cin >> column;
	if (column == -1)
		exit(1);

	row--;
	column--;

	bool is_hit = false;

	if (player_2_board[row][column] == 0 || player_2_board[row][column] == 8)
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Miss!" << endl;
		SetConsoleTextAttribute(hConsole, 15);

		player_2_board[row][column] = 5;
	}

	else if (player_2_board[row][column] == 4)
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << "Hit!" << endl;
		SetConsoleTextAttribute(hConsole, 15);

		is_hit = true;
	}

	else if (player_2_board[row][column] == 3)
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << "Hit!" << endl;
		SetConsoleTextAttribute(hConsole, 15);

		is_hit = true;
	}

	else if (player_2_board[row][column] == 2)
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << "Hit!" << endl;
		SetConsoleTextAttribute(hConsole, 15);

		is_hit = true;
	}

	else if (player_2_board[row][column] == 1)
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << "The ship has been destroyed!" << endl;
		SetConsoleTextAttribute(hConsole, 15);
		Sleep(1000);
		player_2_board[row][column] = 7;
		player_2_ship_count -= 1;

		if (player_2_ship_count == 0) return true;

		SetNotPlacableZone(player_2_board, row, column, row, column, 0);

		PlayerHits(player_1_board, player_2_board, player_2_ship_count);
	}

	
	
	// if player hits enemy ship
	if (is_hit)
	{
		int type_of_ship = player_2_board[row][column];
		player_2_board[row][column] = 6;

		bool is_dead = IsDead(player_2_board, type_of_ship);

		if (is_dead)
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout <<"The ship has been destroyed!" << endl;
			SetConsoleTextAttribute(hConsole, 15);

			vector<int> arr{};

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (player_2_board[i][j] == 6)
					{
						arr.push_back(i);
						arr.push_back(j);
					}
				}
			}

			int horizontal_or_vertical;
			if (arr[0] == arr[2])
				horizontal_or_vertical = 0;
			else
				horizontal_or_vertical = 1;


			SetNotPlacableZone(player_2_board, arr.at(0), arr.at(1), arr.at(size(arr) - 2), arr.at(size(arr) - 1), horizontal_or_vertical);


			player_2_ship_count -= 1;
			ReplaceHitByDead(player_2_board);
		}

		if (player_2_ship_count == 0) return true;

		// hit one more time
		Sleep(1000);
		PlayerHits(player_1_board, player_2_board, player_2_ship_count);

	}

	Sleep(1000);
	return false;
}


void PrintPlayerBoard(int** Board)
{
	/*
	0 - empty
	1, 2, 3, 4 - ship of respective size
	5 - enemy miss
	6 - ship hit
	7 - ship dead
	8 - impossible to place the ship (for initializing computer board)
	*/

	cout << "   ";
	for (int i = 0; i < 10; i++)
		cout << i + 1 << " ";

	cout << endl;
	for (int i = 0; i < 10; i++)
	{

		cout << i + 1;
		if (i + 1 < 10)
			cout << "  ";
		else
			cout << " ";


		for (int j = 0; j < 10; j++)
		{
			if (Board[i][j] == 0)
				cout << "_ ";
			else if (Board[i][j] == 1 || Board[i][j] == 2 || Board[i][j] == 3 || Board[i][j] == 4)
				cout << "s ";
			else if (Board[i][j] == 5)
				cout << "o ";
			else if (Board[i][j] == 6)
				cout << "/ ";
			else if (Board[i][j] == 8)
				cout << "_ ";

			else
				cout << "x ";
		}

		cout << endl;
	}
}





			/*	Help Functions	*/

bool IsDead(int** Board, int type_of_ship)
{
	int count = 0;
	// For 4 square length ship

	if (type_of_ship == 4) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (Board[i][j] == 4) {
					return false;
				}
			}
		}
	}

	if (type_of_ship == 4)
		return true; 
	

	else if (type_of_ship == 3)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (Board[i][j] == 3)
					count++;
			}

			if (count > 3) return false;

		}

		// If there are only 3 squares with number 3(which means that there is only 1 3-square-length ship left)
		if (count == 3 || count == 0)
			return true;
		else return false;
	}



	else if (type_of_ship == 2)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (Board[i][j] == 2)
					count++;
			}

			if (count > 4) return false;

		}

		if (count == 0 || count == 2 || count == 4)
			return true;
		else return false;
	}

	return false;

}


void ReplaceHitByDead(int** Board)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (Board[i][j] == 6)
				Board[i][j] = 7;
}


void SetNotPlacableZone(int** Board, int start_row, int start_column, int end_row, int end_column, int horizontal_or_vertical)
{
	// horizontal ship case
	if (horizontal_or_vertical == 0)
	{

		// leftmost part
		if (start_column != 0 && Board[start_row][start_column - 1] != 5)
			Board[start_row][start_column - 1] = 8;



		// rightmost part
		if (end_column != 9 && Board[start_row][end_column + 1] != 5)
			Board[start_row][end_column + 1] = 8;



		// up and down parts
		for (int i = start_column; i <= start_column + (end_column - start_column); i++)
		{
			if (start_row != 0 && Board[start_row - 1][i] != 5)
				Board[start_row - 1][i] = 8;

			if (start_row != 9 && Board[start_row + 1][i] != 5)
				Board[start_row + 1][i] = 8;
		}


		// corners

		// left up
		if (start_column != 0 && start_row != 0 && Board[start_row - 1][start_column - 1] != 5)
			Board[start_row - 1][start_column - 1] = 8;

		// left down
		if (start_column != 0 && end_row != 9 && Board[start_row + 1][start_column - 1] != 5)
			Board[start_row + 1][start_column - 1] = 8;

		// right up
		if (end_column != 9 && start_row != 0 && Board[end_row - 1][end_column + 1] != 5)
			Board[end_row - 1][end_column + 1] = 8;

		// right down
		if (end_column != 9 && end_row != 9 && Board[end_row + 1][end_column + 1] != 5)
			Board[end_row + 1][end_column + 1] = 8;

	}

	// vertical ship case
	else
	{


		// upmost part
		if (start_row != 0 && Board[start_row - 1][start_column] != 5)
			Board[start_row - 1][start_column] = 8;


		// downmost part
		if (end_row != 9 && Board[end_row + 1][start_column] != 5)
			Board[end_row + 1][start_column] = 8;



		// left and right parts
		for (int i = start_row; i <= start_row + (end_row - start_row); i++)
		{
			if (start_column != 0 && Board[i][start_column - 1] != 5)
				Board[i][start_column - 1] = 8;

			if (start_column != 9 && Board[i][start_column + 1] != 5)
				Board[i][start_column + 1] = 8;
		}



		// corners

		// left up
		if (start_column != 0 && start_row != 0 && Board[start_row - 1][start_column - 1] != 5)
			Board[start_row - 1][start_column - 1] = 8;

		// left down
		if (start_column != 0 && end_row != 9 && Board[end_row + 1][start_column - 1] != 5)
			Board[end_row + 1][start_column - 1] = 8;

		// right up
		if (end_column != 9 && start_row != 0 && Board[start_row - 1][end_column + 1] != 5)
			Board[start_row - 1][end_column + 1] = 8;

		// right down
		if (end_column != 9 && end_row != 9 && Board[end_row + 1][end_column + 1] != 5)
			Board[end_row + 1][end_column + 1] = 8;




	}

}


void PrintExampleOfShipPlacing()
{
	cout << "Place from left to right or top down\t" << endl;
	cout << "\nExample of ship placement: " << endl;
	cout << "    2\t\t3\t    2\t      6" << endl;
	cout << "    ^\t\t^\t    ^\t      ^" << endl;

	cout << "Start row  Start column  End row  End column" << endl;
	


}


void PrintExampleOfShipPlacingForOneLengthShip()
{
	cout << "Example of ship placement: " << endl;
	cout << "    2\t  3" << endl;
	cout << "    ^\t  ^" << endl;

	cout << "   Row\tColumn" << endl;
}
