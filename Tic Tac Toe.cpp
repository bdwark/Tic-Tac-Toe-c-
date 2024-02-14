#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

struct Move //probally didn't need a struct for this but it helps to rember these are connected and prevents overloading
{
	int row, col;
};
Move grid_move;
char grid[3][3] = { {'_','_','_'},{'_','_','_'},{'_','_','_'} }; //the grid that holds the current board state
int grid_ref[3][3] = { {1,2,3},{4,5,6},{7,8,9} }; //refrence grid for show_grid and for when the AI makes a move
int choice; //this is so you can pass numbers to the place move function
char turn = 'X'; //This is setting up the turn order so X goes first
bool draw = false; //Sets the draw variable= to false
int game_mode; //
char single_player_token = '_', AI_token = '_';
int number_of_wins_X = 0, number_of_wins_O = 0, number_of_player_wins = 0, number_of_AI_wins = 0;
char play_again;
void refresh_game();
void player_turn_2P();
void player_turn_AI();

//This function actually places the X and Os on the board
void place_move(int c) {
	//this is a switch table. While it functions almost entirely the same as
	//an if else statement, it looks cleaner and is ever so slighly more efficent
	switch (c) {
	case 1: grid_move.row = 0; grid_move.col = 0; break;
	case 2: grid_move.row = 0; grid_move.col = 1; break;
	case 3: grid_move.row = 0; grid_move.col = 2; break;
	case 4: grid_move.row = 1; grid_move.col = 0; break;
	case 5: grid_move.row = 1; grid_move.col = 1; break;
	case 6: grid_move.row = 1; grid_move.col = 2; break;
	case 7: grid_move.row = 2; grid_move.col = 0; break;
	case 8: grid_move.row = 2; grid_move.col = 1; break;
	case 9: grid_move.row = 2; grid_move.col = 2; break;
	default:
		//if the player puts in something other than 1-9
		cout << "Invalid Move" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		switch (game_mode) {
		case 1: player_turn_2P();
		case 2: player_turn_AI();
		}
	}

	if (turn == 'X' && grid[grid_move.row][grid_move.col] == '_')
	{
		grid[grid_move.row][grid_move.col] = 'X';
		if (turn != single_player_token && single_player_token != '_')
		{
			cout << "\nComputers Move: " << c << endl;
		}
		turn = 'O';
		refresh_game();
	}
	else if (turn == 'O' && grid[grid_move.row][grid_move.col] == '_')
	{
		grid[grid_move.row][grid_move.col] = 'O';
		if (turn != single_player_token && single_player_token != '_') {
			cout << "\nComputers Move: " << c << endl;
		}
		turn = 'X';
		refresh_game();
	}
	else {
		if (game_mode == 1)
		{
			cout << "Box already filled! Please choose another!!!" << endl;
			refresh_game();
		}
		else if (turn == single_player_token)
		{
			cout << "Box already filled! Please choose another!!!" << endl;
			player_turn_AI();
		}
		else
		{
			player_turn_AI();
		}
	}
}

//This functiom contains the logic for the single player mode
void player_turn_AI() {
	//This determins if it the players turn or the AIs turn
	if (turn == single_player_token)
	{
		cout << endl << "      Your  Turn: ";
		cin >> choice;
		place_move(choice);
	}
	else if (turn == AI_token)
	{
		//if the player doesn't take the middle than the AI takes it
		//this is because it is always the most opital move in tik tac toe
		if (grid[1][1] == '_')
		{
			place_move(5);
		}
		//These if statments check for every instance where two X's or O's
		//sit next to each other. If it finds one places the AI token to
		//block or win 
		for (int i = 0; i < 3; i++)
		{
			//This checks every horizontal move for tokens
			if (grid[i][1] == grid[i][2] && grid[i][1] != '_')
			{
				if (grid[i][0] == '_')
				{
					place_move(grid_ref[i][0]);
				}

			}
			else if (grid[i][1] == grid[i][0] && grid[i][1] != '_')
			{
				if (grid[i][2] == '_')
				{
					place_move(grid_ref[i][2]);
				}

			}
			else if (grid[1][i] == grid[2][i] && grid[1][i] != '_')
			{
				if (grid[0][i] == '_')
				{
					place_move(grid_ref[0][i]);
				}
			}
			else if (grid[1][i] == grid[0][i] && grid[1][i] != '_')
			{
				if (grid[2][i] == '_')
				{
					place_move(grid_ref[2][i]);
				}
			}
			else if (grid[0][i] == grid[2][i] && grid[0][i] != '_')
			{
				if (grid[1][i] == '_')
				{
					place_move(grid_ref[1][i]);
				}
			}
			else if (grid[i][0] == grid[i][2] && grid[i][0] != '_')
			{
				if (grid[i][1] == '_')
				{
					place_move(grid_ref[i][1]);
				}
			}
		}

		//This checks for diagonal moves 
		if (grid[0][0] == grid[1][1] && grid[1][1] != '_')
		{
			if (grid[2][2] == '_')
			{
				place_move(grid_ref[2][2]);
			}
		}
		else if (grid[2][2] == grid[1][1] && grid[1][1] != '_')
		{
			if (grid[0][0] == '_')
			{
				place_move(grid_ref[0][0]);
			}
		}
		else if (grid[0][2] == grid[1][1] && grid[1][1] != '_')
		{
			if (grid[2][0] == '_')
			{
				place_move(grid_ref[2][0]);
			}
		}
		else if (grid[2][0] == grid[1][1] && grid[1][1] != '_')
		{
			if (grid[0][2] == '_')
			{
				place_move(grid_ref[0][2]);
			}
		}

		//if it finds nothing then it picks a move at random
		place_move((rand() % 9) + 1);
	}

}

//This function contains the logic for the 2 player mode
void player_turn_2P() {
	switch (turn) {
	case 'X': cout << endl << "    Player 1 turn: "; break;
	case 'O': cout << endl << "    Player 2 turn: "; break;
	}
	cin >> choice;
	place_move(choice);
}

//checks if game is over. If it is it returns true and the game ends
bool gameover_checker() {
	//checks for horizontal and vertical wins. It interates through the columes
	//and rows for if 3 tokens in a colume or row equal the same value and if 
	//that value is X or O. This is so it doesn't end the game on start
	for (int i = 0; i < 3; i++)
		if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != '_' ||
			grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != '_')
		{
			return true;
		}
	//check for diagonal wins. It looks to see if the tokens for all 
	//3 spaces equals the same value. Then it checks if those tokens are 
	//X or O. This is because otherwise it would return game over on start
	if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2] && grid[0][0] != '_' ||
		grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0] && grid[0][2] != '_')
	{
		return true;
	}
	//this checks if the board is full. If not then it returns flase
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (grid[i][j] == '_') {
				return false;
			}
	draw = true;
	return true;
}

//the main function
int main()
{
	//thi sets up the random number generator
	srand(time(0));
	cout << endl;
	cout << "==========================" << endl;
	cout << "     TICK   TAC   TOE " << endl;
	cout << "==========================" << endl;
	cout << "Type '1' for two player mode. Type '2' to play againt an AI" << endl;

	//switch that determines the game mode
	cin >> game_mode;
	switch (game_mode) {
	case 1:
		cout << "FOR 2 PLAYERS" << endl;
		refresh_game();
	case 2: cout << "SINGLE PLAYER" << endl;
		while (1 == 1)
		{
			cout << "Play as X or O?" << endl;

			cin >> single_player_token;
			if ((single_player_token == 'X') || (single_player_token == 'O'))
			{
				if (single_player_token == 'X')
				{
					AI_token = 'O';
				}
				else if (single_player_token == 'O')
				{
					AI_token = 'X';
				}
				refresh_game();
			}
			cout << "  Error: Trying retyping it" << endl;
			cin.clear();
			cin.ignore(10000, '\n');

		}
	default:
		cout << "Error: Unkown Command" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		main();
	}
}

//This function with show the board
void show_grid() {
	//switch that displays the different number of wins for each game mode
	switch (game_mode) {
	case 1: cout << "\n     Wins for X: " << number_of_wins_X << "\n     Wins for O: " << number_of_wins_O << endl; break;
	case 2: cout << "\n      Your Wins: " << number_of_player_wins << "\n     Wins for AI: " << number_of_AI_wins << endl; break;
	}
	//game board displayed with ASCII art
	cout << "     =============" << endl;
	cout << "      Grid layout" << endl;

	//since the board reffrence is held in an array, 
	//this itterates through and displays the board
	for (int i = 0; i < 3; i++)
	{
		cout << "        ";
		for (int j = 0; j < 3; j++)
		{
			cout << grid_ref[i][j] << "  ";
			if (((j + 1) % 3) == 0)
			{
				cout << endl;
			}
		}
	}
	cout << "\n     =============" << endl;
	cout << "      Grid  State" << endl;

	//since the current board state is held in an array, 
	//this itterates through and displays the board
	for (int i = 0; i < 3; i++)
	{
		cout << "        ";
		for (int j = 0; j < 3; j++)
		{
			cout << grid[i][j] << "  ";
			if (((j + 1) % 3) == 0)
			{
				cout << endl;
			}
		}
	}
	cout << "\n     =============";
}

//this function refresses the game. It could probally be merged into main() 
//but for sake of making the code look and maintable clean this looks best
void refresh_game() {
	//this function and links up to the player turns 
	if (gameover_checker() == true)
	{
		if (game_mode == 1) {
			if (turn == 'O' && draw == false)
			{
				cout << "\nCongratulations! Player 1 has won the game!" << endl;
				number_of_wins_X++;
			}
			else if (turn == 'X' && draw == false)
			{
				cout << "\nCongratulations! Player 2 has won the game!" << endl;
				number_of_wins_O++;
			}
		}
		else if (game_mode == 2)
		{
			if (turn == AI_token && draw == false)
			{
				cout << "\nCongratulations! You have won the game!" << endl;
				number_of_player_wins++;
			}
			else if (turn == single_player_token  && draw == false)
			{
				cout << "\nUnfortunately, The AI has won" << endl;
				number_of_AI_wins++;
			}
		}
		else
			cout << "    GAME DRAW!!!" << endl;
		show_grid();
		//while this loop would techinally never end. You are only ether closing 
		//the program or playing again. The loop is if you put in the wrong command
		while (1 == 1)
		{
			cout << "\nDo you want to play again? Y/N" << endl;
			cin >> play_again;

			//does this so it ignore the case of the character
			if (play_again == 'Y' || play_again == 'y')
			{
				//resets variables and clears the array to set up for a new game
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						grid[i][j] = '_';
					}
				}
				play_again = ' ';
				draw = false;
				turn = 'X';
				main();
			}
			else if (play_again == 'N' || play_again == 'n')
			{
				exit(0);
			}
			else {
				cout << "Invalid Command" << endl;
			}
		}
	}
	switch (game_mode) {
	case 1:
		show_grid();
		player_turn_2P();
	case 2:
		//This is so the program won't show the grid when the AI is making a move. 
		//It will show on you turn
		if (turn == single_player_token)
		{
			show_grid();
			player_turn_AI();
		}
		else if (turn == AI_token)
		{
			player_turn_AI();
		}
	}
}
