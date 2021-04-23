#pragma once

#include <iostream>
#include <time.h>
#include <Windows.h>
#include <vector>

using namespace std;


// return true-when the ship is placed/false-when not 
bool PlaceFourSquareShip(int** Board);
bool PlaceThreeSquareShip(int** Board);
bool PlaceTwoSquareShip(int** Board);
bool PlaceOneSquareShip(int** Board);
// return true-when the ship is placed/false-when not 

// return true when hit/false when miss
bool ShootPosition(int** Board, int* targeted_hit_list, int* type_of_ship, int i);
void InitializeComputerBoard(int** Board);
// Hits enemy board in a random position from hit_list
// !!! NO TRACK OF SHOOTS AND DEAD SHIPS
void DumbHit(int** Board, int* hit_list, int& index, int& counter);
int* SmartHit(int** enemy_board, int** your_board, int* hit_list, int& index, int& counter, int* type_of_ship, int* targeted_hit_list, bool& was_hit);
int* SmartHitComputerComputer(int** enemy_board, int** your_board, int* hit_list, int& index, int& counter, int* type_of_ship, int* targeted_hit_list, bool& was_hit);
//void SetNotPlacableZoneForComputer(int** Board, int start_row, int start_column, int end_row, int end_column, int horizontal_or_vertical);
int* InitializeTargetedHitList(int** Board, int* type_of_ship, int row, int column);
int* ReturnToInitialConditionTargetedHitList();
void PrintBoards(int** player_1_board, int** player_2_board);
void PirntComputerBoards(int** player_1_board, int** player_2_board);


					/*  MAIN FUNCTIONS  */

// Initialize randomly computer board
void InitializeComputerBoard(int** Board)
{

	PlaceFourSquareShip(Board);
	for (int i = 0; i < 2; i++)
		PlaceThreeSquareShip(Board);
	for (int i = 0; i < 3; i++)
		PlaceTwoSquareShip(Board);
	for (int i = 0; i < 4; i++)
		PlaceOneSquareShip(Board);
}


// Takes enemy board
void DumbHit(int** Board, int* hit_list, int& index, int& counter)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int row = hit_list[index] / 10;
	int column = hit_list[index] % 10;

	cout << "Hitting: " << row + 1 << " " << column + 1 << endl;
	Sleep(500);

	if (Board[row][column] == 1 || Board[row][column] == 2 || Board[row][column] == 3 || Board[row][column] == 4)
	{
		Board[row][column] = 6;

		SetConsoleTextAttribute(hConsole, 10);
		cout << "Hit!" << endl;
		SetConsoleTextAttribute(hConsole, 15);

		index += 1;
		counter -= 1;

		if (counter != 0)
			DumbHit(Board, hit_list, index, counter);
	}

	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Miss!" << endl;
		SetConsoleTextAttribute(hConsole, 15);
		Board[row][column] = 5;
		index += 1;
	}
	Sleep(1000);
}


int* SmartHit(int** enemy_board, int** your_board, int* hit_list, int& index, int& counter, int* type_of_ship, int* targeted_hit_list, bool& was_hit)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	PrintBoards(enemy_board, your_board);

	int row;
	int column;

	// to find next hit point
	// only used when there are no damaged ships to hit
	if (!was_hit)
	{
		row = hit_list[index] / 10;
		column = hit_list[index] % 10;

		index += 1;

		while (enemy_board[row][column] == 5 || enemy_board[row][column] == 6 || enemy_board[row][column] == 7 || enemy_board[row][column] == 8)
		{
			row = hit_list[index] / 10;
			column = hit_list[index] % 10;

			index += 1;
		}

		cout << "Hitting: (" << row + 1 << ", " << column + 1 << ")" << endl ;
		Sleep(1500);

		if (enemy_board[row][column] == 0)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Miss!" << endl;
			SetConsoleTextAttribute(hConsole, 15);

			enemy_board[row][column] = 5;
		}

		// doesn't change for 6
		else if (enemy_board[row][column] == 2 || enemy_board[row][column] == 3 || enemy_board[row][column] == 4)
		{

			SetConsoleTextAttribute(hConsole, 10);
			cout << "Hit!" << endl;
			SetConsoleTextAttribute(hConsole, 15);
			Sleep(1000);

			type_of_ship[0] = enemy_board[row][column];

			counter -= 1;
			targeted_hit_list = InitializeTargetedHitList(enemy_board, type_of_ship, row, column);
			enemy_board[row][column] = 6;
			was_hit = true;
		}

		// not finished
		else if (enemy_board[row][column] == 1)
		{

			SetConsoleTextAttribute(hConsole, 10);
			cout << "The ship has been destroyed!" << endl << endl;
			SetConsoleTextAttribute(hConsole, 15);

			Sleep(1000);

			counter -= 1;
			enemy_board[row][column] = 7;

			PrintPlayerBoard(enemy_board);

			if (counter == 0)
				return targeted_hit_list;

			SetNotPlacableZone(enemy_board, row, column, row, column, 0);

			SmartHit(enemy_board, your_board, hit_list, index, counter, type_of_ship, targeted_hit_list, was_hit);

		}

	}


	// if there was a hit
	if (was_hit)
	{
		system("cls");
		PrintBoards(enemy_board, your_board);

		// to find next hit point
		int i = 0;
		while (targeted_hit_list[i] == 0)
			i++;



		bool is_hit = ShootPosition(enemy_board, targeted_hit_list, type_of_ship, i);

		if (is_hit)
		{
			counter -= 1;

			if (counter == 0)
			{

				SetConsoleTextAttribute(hConsole, 10);
				cout << "The ship has been destroyed!" << endl << endl;
				SetConsoleTextAttribute(hConsole, 15);
				Sleep(1000);

				return targeted_hit_list;
			}

			bool is_dead = IsDead(enemy_board, type_of_ship[0]);
			if (is_dead)
			{

				SetConsoleTextAttribute(hConsole, 10);
				cout << "The ship has been destroyed!" << endl << endl;
				SetConsoleTextAttribute(hConsole, 15);

				Sleep(1000);

				vector<int> arr{};

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (enemy_board[i][j] == 6)
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


				SetNotPlacableZone(enemy_board, arr.at(0), arr.at(1), arr.at(size(arr) - 2), arr.at(size(arr) - 1), horizontal_or_vertical);

				ReplaceHitByDead(enemy_board);

				type_of_ship[0] = 0;

				system("cls");
				PrintBoards(enemy_board, your_board);

				targeted_hit_list = ReturnToInitialConditionTargetedHitList();

				was_hit = false;
			}


			targeted_hit_list = SmartHit(enemy_board, your_board, hit_list, index, counter, type_of_ship, targeted_hit_list, was_hit);
		}


	}


	return targeted_hit_list;

}

int* SmartHitComputerComputer(int** enemy_board, int** your_board, int* hit_list, int& index, int& counter, int* type_of_ship, int* targeted_hit_list, bool& was_hit)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	PirntComputerBoards(your_board, enemy_board);

	int row;
	int column;

	// to find next hit point
	// only used when there are no damaged ships to hit
	if (!was_hit)
	{
		row = hit_list[index] / 10;
		column = hit_list[index] % 10;

		index += 1;

		while (enemy_board[row][column] == 5 || enemy_board[row][column] == 6 || enemy_board[row][column] == 7 || enemy_board[row][column] == 8)
		{
			row = hit_list[index] / 10;
			column = hit_list[index] % 10;

			index += 1;
		}

		cout << "Hitting: (" << row + 1 << ", " << column + 1 << ")" << endl;
		Sleep(1500);

		if (enemy_board[row][column] == 0)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Miss!" << endl;
			SetConsoleTextAttribute(hConsole, 15);

			enemy_board[row][column] = 5;
		}

		// doesn't change for 6
		else if (enemy_board[row][column] == 2 || enemy_board[row][column] == 3 || enemy_board[row][column] == 4)
		{

			SetConsoleTextAttribute(hConsole, 10);
			cout << "Hit!" << endl;
			SetConsoleTextAttribute(hConsole, 15);
			Sleep(1000);

			type_of_ship[0] = enemy_board[row][column];

			counter -= 1;
			targeted_hit_list = InitializeTargetedHitList(enemy_board, type_of_ship, row, column);
			enemy_board[row][column] = 6;
			was_hit = true;
		}

		// not finished
		else if (enemy_board[row][column] == 1)
		{

			SetConsoleTextAttribute(hConsole, 10);
			cout << "The ship has been destroyed!" << endl << endl;
			SetConsoleTextAttribute(hConsole, 15);

			Sleep(1000);

			counter -= 1;
			enemy_board[row][column] = 7;


			if (counter == 0)
				return targeted_hit_list;

			SetNotPlacableZone(enemy_board, row, column, row, column, 0);

			SmartHit(enemy_board, your_board, hit_list, index, counter, type_of_ship, targeted_hit_list, was_hit);

		}

	}


	// if there was a hit
	if (was_hit)
	{
		system("cls");
		PirntComputerBoards(your_board, enemy_board);

		// to find next hit point
		int i = 0;
		while (targeted_hit_list[i] == 0)
			i++;



		bool is_hit = ShootPosition(enemy_board, targeted_hit_list, type_of_ship, i);

		if (is_hit)
		{
			counter -= 1;

			if (counter == 0)
			{

				SetConsoleTextAttribute(hConsole, 10);
				cout << "The ship has been destroyed!" << endl << endl;
				SetConsoleTextAttribute(hConsole, 15);
				Sleep(1000);

				return targeted_hit_list;
			}

			bool is_dead = IsDead(enemy_board, type_of_ship[0]);
			if (is_dead)
			{

				SetConsoleTextAttribute(hConsole, 10);
				cout << "The ship has been destroyed!" << endl << endl;
				SetConsoleTextAttribute(hConsole, 15);

				Sleep(1000);

				vector<int> arr{};

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (enemy_board[i][j] == 6)
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


				SetNotPlacableZone(enemy_board, arr.at(0), arr.at(1), arr.at(size(arr) - 2), arr.at(size(arr) - 1), horizontal_or_vertical);

				ReplaceHitByDead(enemy_board);

				type_of_ship[0] = 0;

				system("cls");
				PirntComputerBoards(your_board, enemy_board);

				targeted_hit_list = ReturnToInitialConditionTargetedHitList();

				was_hit = false;
			}


			targeted_hit_list = SmartHitComputerComputer(enemy_board, your_board, hit_list, index, counter, type_of_ship, targeted_hit_list, was_hit);
		}


	}


	return targeted_hit_list;

}


					/*  HELP FUNCTIONS   */

// from 1 to 100
// 0 on targeted_hit_list means that the position will not be hit
int* InitializeTargetedHitList(int** Board, int* type_of_ship, int row, int column)
{
	int* initialized_targeted_hit_list = new int[(type_of_ship[0] - 1) * 4];

	int index = 0;
	bool up = true;
	bool down = true;
	bool left = true;
	bool right = true;

		// up
		if (row != 0)
		{
			for (int i = 1; i < type_of_ship[0]; i++)
			{
				if (row - i >= 0 && Board[row - i][column] != 5 && Board[row - i][column] != 8 && up)
				{
					initialized_targeted_hit_list[index] = (10 * (row - i) + (column)) + 1;
					index++;
				}
				else
				{
					up = false;
					initialized_targeted_hit_list[index] = 0;
					index++;
				}
			}
		}



		// down 
		if (row != 9)
		{
			for (int i = 1; i < type_of_ship[0]; i++)
			{
				if (row + i <= 9 && Board[row + i][column] != 5 && Board[row + i][column] != 8 && down)
				{
					initialized_targeted_hit_list[index] = (10 * (row + i) + (column)) + 1;
					index++;
				}
				else
				{
					down = false;
					initialized_targeted_hit_list[index] = 0;
					index++;
				}
			}
		}



		// left
		if (column != 0)
		{
			for (int i = 1; i < type_of_ship[0]; i++)
			{
				if (column - i >= 0 && Board[row][column - i] != 5 && Board[row][column - i] != 8 && left)
				{
					initialized_targeted_hit_list[index] = (10 * row + (column - i)) + 1;
					index++;
				}
				else
				{
					left = false;
					initialized_targeted_hit_list[index] = 0;
					index++;
				}
			}
		}



		// right
		if (column != 9)
		{
			for (int i = 1; i < type_of_ship[0]; i++)
			{
				if (column + i <= 9 && Board[row][column + i] != 5 && Board[row][column + i] != 8 && right)
				{
					initialized_targeted_hit_list[index] = (10 * row + (column + i)) + 1;
					index++;
				}
				else
				{
					right = false;
					initialized_targeted_hit_list[index] = 0;
					index++;
				}
			}
		}



	return initialized_targeted_hit_list;
}


// To Place 4-square-length ship
bool PlaceFourSquareShip(int** Board)
{

	int horizontal_or_vertical;  // 0 - horizontal 1 - vertical

	int row = 0;  // from 0-9
	int column = 0;  // from 0-9



	horizontal_or_vertical = rand() % 2;



	if (horizontal_or_vertical == 0)
	{
		row = rand() % 10;
		column = rand() % 7;
	}

	else if (horizontal_or_vertical == 1)
	{
		row = rand() % 7;
		column = rand() % 10;
	}





	// horizontal ship
	if (horizontal_or_vertical == 0)
	{

		Board[row][column] = 4;
		Board[row][column + 1] = 4;
		Board[row][column + 2] = 4;
		Board[row][column + 3] = 4;

		SetNotPlacableZone(Board, row, column, row, column + 3, horizontal_or_vertical);

		return true;

	}

	// vertical ship
	else
	{

		Board[row][column] = 4;
		Board[row + 1][column] = 4;
		Board[row + 2][column] = 4;
		Board[row + 3][column] = 4;

		SetNotPlacableZone(Board, row, column, row + 3, column, horizontal_or_vertical);

		return true;

	}

	return false;
}

// To place 3-square-length ship
bool PlaceThreeSquareShip(int** Board)
{


	int horizontal_or_vertical;  // 0 - horizontal 1 - vertical

	int row = 0;  // from 0-9
	int column = 0;  // from 0-9



	horizontal_or_vertical = rand() % 2;


	// find optimal place
	if (horizontal_or_vertical == 0)
	{
		row = rand() % 10;
		column = rand() % 8;


		while (Board[row][column] != 0 || Board[row][column + 1] != 0 || Board[row][column + 2] != 0)
		{
			row = rand() % 10;
			column = rand() % 8;
		}


	}
	else if (horizontal_or_vertical == 1)
	{
		row = rand() % 8;
		column = rand() % 10;

		while (Board[row][column] != 0 || Board[row + 1][column] != 0 || Board[row + 2][column] != 0)
		{
			row = rand() % 8;
			column = rand() % 10;
		}

	}



	// place the ship and set not available zone

	//horizontal ship 
	if (horizontal_or_vertical == 0)
	{
		Board[row][column] = 3;
		Board[row][column + 1] = 3;
		Board[row][column + 2] = 3;

		SetNotPlacableZone(Board, row, column, row, column + 2, horizontal_or_vertical);

		return true;

	}


	// vertical ship
	else
	{
		Board[row][column] = 3;
		Board[row + 1][column] = 3;
		Board[row + 2][column] = 3;

		SetNotPlacableZone(Board, row, column, row + 2, column, horizontal_or_vertical);

		return true;


	}

	return false;
}


// To place 2-square-length-ship
bool PlaceTwoSquareShip(int** Board)
{


	int horizontal_or_vertical;  // 0 - horizontal 1 - vertical

	int row = 0;  // from 0-9
	int column = 0;  // from 0-9



	horizontal_or_vertical = rand() % 2;



	if (horizontal_or_vertical == 0)
	{

		row = rand() % 10;
		column = rand() % 9;


		while (Board[row][column] != 0 || Board[row][column + 1] != 0)
		{
			row = rand() % 10;
			column = rand() % 9;
		}


	}
	else if (horizontal_or_vertical == 1)
	{

		row = rand() % 9;
		column = rand() % 10;


		while (Board[row][column] != 0 || Board[row + 1][column] != 0)
		{
			row = rand() % 9;
			column = rand() % 10;
		}


	}



	// place the ship and set not available zone

	// horizontal ship case
	if (horizontal_or_vertical == 0)
	{
		Board[row][column] = 2;
		Board[row][column + 1] = 2;

		SetNotPlacableZone(Board, row, column, row, column + 1, horizontal_or_vertical);

		return true;
	}



	// vertical ship
	else
	{
		Board[row][column] = 2;
		Board[row + 1][column] = 2;

		SetNotPlacableZone(Board, row, column, row + 1, column, horizontal_or_vertical);


		return true;

	}

	return false;



}


// To place 1-square-length ship
bool PlaceOneSquareShip(int** Board)
{

	int row = rand() % 10;;  // from 0-9
	int column = rand() % 10;;  // from 0-9


	while (Board[row][column] != 0)
	{
		row = rand() % 10;
		column = rand() % 10;
	}


	Board[row][column] = 1;


	SetNotPlacableZone(Board, row, column, row, column, 0);


	return true;

}


// Shoots next point on targeted_hit_list
bool ShootPosition(int** Board, int* targeted_hit_list, int* type_of_ship, int i)
{
	// i - the position to hit
	// values in targeted_hit_list are from 1 to 100
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// point to hit
	int row = (targeted_hit_list[i] - 1) / 10;
	int column = (targeted_hit_list[i] - 1) % 10;

	int border;

	
	cout << "Hitting: (" << row + 1 << ", " << column + 1 << ")"<< endl;
	Sleep(1500);

	targeted_hit_list[i] = 0;

	// miss
	if (Board[row][column] == 0)
	{

		SetConsoleTextAttribute(hConsole, 12);
		cout << "Miss!" << endl;
		SetConsoleTextAttribute(hConsole, 15);
		Sleep(500);

		Board[row][column] = 5;

		// to find the border
		for (int j = i; j < 16; j++)
		{
			if ((j + 1) % (type_of_ship[0] - 1) == 0)
			{
				border = j;
				break;
			}
		}


		// to eliminate shooting same direction after miss
		for (int j = i; j <= border; j++)
			targeted_hit_list[j] = 0;

		return false;
	}


	// if hit
	else if (Board[row][column] == 2 || Board[row][column] == 3 || Board[row][column] == 4)
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << "Hit!" << endl;
		SetConsoleTextAttribute(hConsole, 15);
		Sleep(1000);

		Board[row][column] = 6;
		return true;
	}



}


int* ReturnToInitialConditionTargetedHitList()
{
	int* new_arr = new int[4]{ -1,-1,-1,-1 };

	return new_arr;
}
