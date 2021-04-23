#include <iostream>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include <vector>


#include "Player_functions.h";
#include "Computer_functions.h";

using namespace std;

int** DeclareBoard();  // Declares 10x10 empty board
void CreateHitList(int* arr);  // Creates hit list for computer(Used if player choose to face dumb computer) 
void PrintRules();
void DeleteBoard(int** Board);
void AdoptBoardForPlaying(int** Board);  // Modifies Board to enable smart computer to play
void PrintBoards(int** player_1_board, int** player_2_board);
void PirntComputerBoards(int** player_1_board, int** player_2_board);

int main()
{
	srand(time(NULL));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);

	cout << "\t\tHello and welcome to BATTLESHIP game" << endl << endl;



	// New game
	bool new_game = true;
	while (new_game)
	{
		int play_style;
		cout << "Choose play style\n1-Player vs Computer\n2-Computer vs Computer" << endl;
		cin >> play_style;

		int dumb_smart;
		cout << "Choose computer difficulty level\n1-Dumb Computer(Random shoot, No track of dead ships, No visual representation of dead ships)\n2-Smart Computer" << endl;
		cin >> dumb_smart;


		// player vs computer
		if (play_style == 1)
		{
			// Only declare boards 
			int** player_1_board = DeclareBoard();  // player
			int** player_2_board = DeclareBoard();  // computer


			int random_place;
			cout << "Choose the way of placing ships\n1-Player\n2-Random" << endl;
			cin >> random_place;


			// dumb computer
			if (dumb_smart == 1)
			{
			// INITIALIZING BOARDS

					system("cls");
				
					// initialize player board
					if (random_place == 1)
						InitializePlayerBoard(player_1_board);
					else
						InitializeComputerBoard(player_1_board);


					// initialize computer board
					InitializeComputerBoard(player_2_board);
					AdoptBoardForPlaying(player_2_board);
				
			// INITIALIZING BOARDS	

					
			// ADDITIONAL SETTINGS

					int player_2_ship_count = 10;  // shows the number of ship that enemy of player has
					// Create hit list for computer
					int* array_of_hit_list = new int[100];
					CreateHitList(array_of_hit_list);

					bool this_game = true;  // to continue the current game
					int counter = 20;  // shows the number of squares of player with ships on them
					int index = 0;  // to move across hit list


			// ADDITIONAL SETTINGS


			// START OF GAME
					while (this_game)
					{
						PrintBoards(player_1_board, player_2_board);
						PlayerHits(player_1_board, player_2_board, player_2_ship_count);

						// to check if player won
						if (player_2_ship_count == 0)
						{
							PrintBoards(player_1_board, player_2_board);
							Sleep(2000);
							system("cls");
							cout << "Player won!!!" << endl << endl;
							this_game = false;
							break;
						}


						PrintBoards(player_1_board, player_2_board);
						cout << "Computer turn: " << endl;
						DumbHit(player_1_board, array_of_hit_list, index, counter);

						// to check if computer won
						if (counter == 0)
						{
							PrintBoards(player_1_board, player_2_board);
							Sleep(2000);
							system("cls");
							cout << "Computer won!!!" << endl;
							this_game = false;
							break;
						}
					}

					delete[] array_of_hit_list;
			}
		
		

			// smart computer
			else if (dumb_smart == 2)
			{ 
			// INITIALIZING BOARDS

					system("cls");

					// initialize player board
					if (random_place == 1)
						InitializePlayerBoard(player_1_board);
					else
						InitializeComputerBoard(player_1_board);


					// initialize computer board
					InitializeComputerBoard(player_2_board);

					AdoptBoardForPlaying(player_1_board);
					AdoptBoardForPlaying(player_2_board);

			// INITIALIZING BOARDS	
			

			// ADDITIONAL SETTINGS

					int player_2_ship_count = 10;  // shows the number of ship that enemy of player has
					// Create hit list for computer
					int* array_of_hit_list = new int[100];
					CreateHitList(array_of_hit_list);

					bool this_game = true;  // to continue the current game
					int counter = 20;  // shows the number of squares of player with ships on them
					int index = 0;  // to move across hit list

					int* targeted_hit_list = new int[4];
					targeted_hit_list[0] = -1;
					int* type_of_ship = new int[1]{ 0 };
					bool was_hit = false;

			// ADDITIONAL SETTINGS


			// START OF GAME
					while(this_game)
					{
						PrintBoards(player_1_board, player_2_board);
						PlayerHits(player_1_board, player_2_board, player_2_ship_count);

						// to check if player won
						if (player_2_ship_count == 0)
						{
							PrintBoards(player_1_board, player_2_board);
							Sleep(2000);
							system("cls");
							cout << "Player won!!!" << endl << endl;
							this_game = false;
							break;
						}


						PrintBoards(player_1_board, player_2_board);
						targeted_hit_list = SmartHit(player_1_board, player_2_board, array_of_hit_list, index, counter, type_of_ship, targeted_hit_list, was_hit);

						// to check if computer won
						if (counter == 0)
						{
							PrintBoards(player_1_board, player_2_board);
							Sleep(2000);
							system("cls");
							cout << "Computer won!!!" << endl;
							this_game = false;
							break;
						}
					}

					delete[] array_of_hit_list;
					delete[] targeted_hit_list;
					delete[] type_of_ship;
			}
				
		

			// After game ended
			DeleteBoard(player_1_board);
			DeleteBoard(player_2_board);
		}



		// computer vs computer
		else if (play_style == 2)
		{
			// Only declare boards 
			int** player_1_board = DeclareBoard();  // player
			int** player_2_board = DeclareBoard();  // computer
			

			// dumb computer
			if (dumb_smart == 1)
			{
				// INITIALIZING BOARDS

						system("cls");

						// initialize computer boards
						InitializeComputerBoard(player_1_board);
						AdoptBoardForPlaying(player_1_board);

						InitializeComputerBoard(player_2_board);
						AdoptBoardForPlaying(player_2_board);

				// INITIALIZING BOARDS	


				// ADDITIONAL SETTINGS

						// Create hit list for computer
						int* array_of_hit_list1 = new int[100];
						int* array_of_hit_list2 = new int[100];
						CreateHitList(array_of_hit_list1);
						CreateHitList(array_of_hit_list2);

						// to move across hit list
						int index_computer_1 = 0;
						int index_computer_2 = 0;

						// shows the number of squares of player with ships on them
						int counter_computer_1 = 20;
						int counter_computer_2 = 20;

						bool this_game = true;  // to continue the current game

				// ADDITIONAL SETTINGS


				// START OF GAME
						while (this_game)
						{
							// computer 1 shoots
							PirntComputerBoards(player_1_board, player_2_board);
							cout << "Computer 1 turn: " << endl;
							DumbHit(player_2_board, array_of_hit_list1, index_computer_1, counter_computer_1);

							// to check if computer 1 won
							if (counter_computer_1 == 0)
							{
								PirntComputerBoards(player_1_board, player_2_board);
								Sleep(2000);
								system("cls");
								cout << "Player 1 won!!!" << endl << endl;
								this_game = false;
								break;
							}

							// computer 2 shoots
							PirntComputerBoards(player_1_board, player_2_board);
							cout << "Computer 2 turn: " << endl;
							DumbHit(player_1_board, array_of_hit_list2, index_computer_2, index_computer_2);

							// to check if computer won
							if (counter_computer_2 == 0)
							{
								PirntComputerBoards(player_1_board, player_2_board);
								Sleep(2000);
								system("cls");
								cout << "Player 2 won!!!" << endl;
								this_game = false;
								break;
							}


						}

						delete[] array_of_hit_list1;
						delete[] array_of_hit_list2;
			}
			
			
			
			else if (dumb_smart == 2)
			{
				
			// INITIALIZING BOARDS

					system("cls");

					// initialize computer boards
					InitializeComputerBoard(player_1_board);
					AdoptBoardForPlaying(player_1_board);

					InitializeComputerBoard(player_2_board);
					AdoptBoardForPlaying(player_2_board);

			// INITIALIZING BOARDS	


			// ADDITIONAL SETTINGS

							// Create hit list for computer
					int* array_of_hit_list1 = new int[100];
					int* array_of_hit_list2 = new int[100];
					CreateHitList(array_of_hit_list1);
					CreateHitList(array_of_hit_list2);

					// to move across hit list
					int index_computer_1 = 0;
					int index_computer_2 = 0;

					// shows the number of squares of player with ships on them
					int counter_computer_1 = 20;
					int counter_computer_2 = 20;

					int* targeted_hit_list1 = new int[4];
					targeted_hit_list1[0] = -1;
					int* type_of_ship1 = new int[1]{ 0 };
					bool was_hit1 = false;

					int* targeted_hit_list2 = new int[4];
					targeted_hit_list2[0] = -1;
					int* type_of_ship2 = new int[1]{ 0 };
					bool was_hit2 = false;

					bool this_game = true;  // to continue the current game

			// ADDITIONAL SETTINGS

					cout << "\n\n\n\n\n\n\n\n\n\n\n";
					cout << "\t\t\t\t\tYou chose gamestyle:\n\t\t\t\t smart computer vs smart computer\n\n";
					cout << "\t\tYou will see the game from the side of the 1st computer and then from the second";
					cout << "\n\n\n";
					system("pause");

			// START OF GAME
					while (this_game)
					{
						// computer 1 shoots
						PirntComputerBoards(player_1_board, player_2_board);
						cout << "Computer 1 turn: " << endl;
						targeted_hit_list1 = SmartHitComputerComputer(player_2_board, player_1_board, array_of_hit_list1, index_computer_1, counter_computer_1, type_of_ship1, targeted_hit_list1, was_hit1);

						// to check if computer 1 won
						if (counter_computer_1 == 0)
						{
							PirntComputerBoards(player_1_board, player_2_board);
							Sleep(2000);
							system("cls");
							cout << "Player 1 won!!!" << endl << endl;
							this_game = false;
							break;
						}

						// computer 2 shoots
						PirntComputerBoards(player_1_board, player_2_board);
						cout << "Computer 2 turn: " << endl;
						targeted_hit_list2 = SmartHitComputerComputer(player_1_board, player_2_board, array_of_hit_list2, index_computer_2, counter_computer_2, type_of_ship2, targeted_hit_list2, was_hit2);


						// to check if computer won
						if (counter_computer_2 == 0)
						{
							PirntComputerBoards(player_1_board, player_2_board);
							Sleep(2000);
							system("cls");
							cout << "Player 2 won!!!" << endl;
							this_game = false;
							break;
						}


					}

					delete[] targeted_hit_list1;
					delete[] type_of_ship1;

					delete[] targeted_hit_list2;
					delete[] type_of_ship2;

					delete[] array_of_hit_list1;
					delete[] array_of_hit_list2;
				
			}



			// After game ended
			DeleteBoard(player_1_board);
			DeleteBoard(player_2_board);
		}




		// to start another game or quit

		char to_continue;
		cout << "Another game?(y/n): ";
		cin >> to_continue;

		if (to_continue == 'n')
		{
			new_game = false;
		}
	}



	return 0;
}



int** DeclareBoard()
{
	int** board = new int* [10];
	for (int i = 0; i < 10; i++)
		board[i] = new int[10]{};

	return board;
}

void CreateHitList(int* arr)
{
	// gets an empty array 
	// fills with random numbers from 0 to 99

	int random_index;
	int temp;

	for (int i = 0; i < 100; i++)
		arr[i] = i;
	
	// shuffles the array
	for (int i = 0; i < 100; i++)
	{
		random_index = rand() % 100;
		temp = arr[random_index];
		arr[random_index] = arr[i];
		arr[i] = temp;
	}

	for (int i = 0; i < 100; i++)
	{
		random_index = rand() % 100;
		temp = arr[random_index];
		arr[random_index] = arr[i];
		arr[i] = temp;
	}

	for (int i = 0; i < 100; i++)
	{
		random_index = rand() % 100;
		temp = arr[random_index];
		arr[random_index] = arr[i];
		arr[i] = temp;
	}
}

void PrintRules()
{
	cout << "\t\t\t\t   Meaning of symbols:" << endl;
	cout << "\t\t\t\t\"_\"-empty\n";
	cout << "\t\t\t\t\"o\"-miss\n";
	cout << "\t\t\t\t\"s\"-your ship\n";
	cout << "\t\t\t\t\"/\"-hit\n";
	cout << "\t\t\t\t\"x\"-dead\n\n";
}

void DeleteBoard(int** Board)
{
	for (int i = 0; i < 10; i++)
		delete[] Board[i];
	delete[] Board;
	Board = nullptr;
}

void AdoptBoardForPlaying(int** Board)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (Board[i][j] == 8)
				Board[i][j] = 0;
}

void PrintBoards(int** player_1_board, int** player_2_board)
{
	/*
	0 - empty
	1, 2, 3, 4 - ship of respective size
	5 - enemy miss
	6 - ship hit
	7 - ship dead
	8 - impossible to place the ship (for initializing computer board)
	*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");
	PrintRules();

	cout << "     Player board: \t\t\t\t\t     Computer board: \n";
	cout << "   ";
	for (int i = 1; i <= 10; i++)
		cout << i << " ";
	cout << "\t\t\t\t ";
	cout << "  ";
	for (int i = 1; i <= 10; i++)
		cout << i << " ";
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
			if (player_1_board[i][j] == 0)
				cout << "_ ";
			else if (player_1_board[i][j] == 1 || player_1_board[i][j] == 2 || player_1_board[i][j] == 3 || player_1_board[i][j] == 4)
				cout << "s ";
			else if (player_1_board[i][j] == 5)
				cout << "o ";
			else if (player_1_board[i][j] == 6)
			{
				SetConsoleTextAttribute(hConsole, 12);

				cout << "/ ";
				SetConsoleTextAttribute(hConsole, 15);
			}
			else if (player_1_board[i][j] == 8)
				cout << "_ ";
			else
			{
				SetConsoleTextAttribute(hConsole, 12);

				cout << "x ";
				SetConsoleTextAttribute(hConsole, 15);
			}
		}


		cout << "\t\t\t\t\t";

		cout << i + 1;
		if (i + 1 < 10)
			cout << "  ";
		else
			cout << " ";

		for (int j = 0; j < 10; j++)
		{
			if (player_2_board[i][j] == 0)
				cout << "_ ";
			else if (player_2_board[i][j] == 1 || player_2_board[i][j] == 2 || player_2_board[i][j] == 3 || player_2_board[i][j] == 4)
				cout << "_ ";
			else if (player_2_board[i][j] == 5)
				cout << "o ";
			else if (player_2_board[i][j] == 6)
			{
				SetConsoleTextAttribute(hConsole, 12);

				cout << "/ ";
				SetConsoleTextAttribute(hConsole, 15);
			}
			else if (player_2_board[i][j] == 8)
				cout << "o ";
			else
			{
				SetConsoleTextAttribute(hConsole, 12);

				cout << "x ";
				SetConsoleTextAttribute(hConsole, 15);
			}
		}

		cout << endl;



	}




	cout << endl;
	cout << endl;
}

void PirntComputerBoards(int** player_1_board, int** player_2_board)
{
	/*
	0 - empty
	1, 2, 3, 4 - ship of respective size
	5 - enemy miss
	6 - ship hit
	7 - ship dead
	8 - impossible to place the ship (for initializing computer board)
	*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");
	PrintRules();

	cout << "   Your board: \t\t\t\t\t\t   Enemy board: \n";
	cout << "   ";
	for (int i = 1; i <= 10; i++)
		cout << i << " ";
	cout << "\t\t\t\t ";
	cout << "  ";
	for (int i = 1; i <= 10; i++)
		cout << i << " ";
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
			if (player_1_board[i][j] == 0)
				cout << "_ ";
			else if (player_1_board[i][j] == 1 || player_1_board[i][j] == 2 || player_1_board[i][j] == 3 || player_1_board[i][j] == 4)
				cout << "_ ";
			else if (player_1_board[i][j] == 5)
				cout << "o ";
			else if (player_1_board[i][j] == 6)
			{
				SetConsoleTextAttribute(hConsole, 12);

				cout << "/ ";
				SetConsoleTextAttribute(hConsole, 15);
			}
			else if (player_1_board[i][j] == 8)
				cout << "o ";
			else
			{
				SetConsoleTextAttribute(hConsole, 12);

				cout << "x ";
				SetConsoleTextAttribute(hConsole, 15);
			}
		}



		cout << "\t\t\t\t\t";

		cout << i + 1;
		if (i + 1 < 10)
			cout << "  ";
		else
			cout << " ";

		for (int j = 0; j < 10; j++)
		{
			if (player_2_board[i][j] == 0)
				cout << "_ ";
			else if (player_2_board[i][j] == 1 || player_2_board[i][j] == 2 || player_2_board[i][j] == 3 || player_2_board[i][j] == 4)
				cout << "_ ";
			else if (player_2_board[i][j] == 5)
				cout << "o ";
			else if (player_2_board[i][j] == 6)
			{
				SetConsoleTextAttribute(hConsole, 12);

				cout << "/ ";
				SetConsoleTextAttribute(hConsole, 15);
			}
			else if (player_2_board[i][j] == 8)
				cout << "o ";
			else
			{
				SetConsoleTextAttribute(hConsole, 12);

				cout << "x ";
				SetConsoleTextAttribute(hConsole, 15);
			}
		}

		cout << endl;
	}

	cout << endl;
	cout << endl;

}
