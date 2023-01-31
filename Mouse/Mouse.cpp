// Name: Kareem A. Mohammed Talaat 
// ID: 900192903
// Assignment #1
// The mouse on the island game



#include <iostream>
using namespace std;
#include <time.h>
#define o 25   //here we include system time so we can randomize numbers and get different results, and also declared o which is the maximum size of the island 



int Initialise_Scene(char arr[][o], int& a, int& b, char& Cat, int n) // Here we use this function to set our scene in the 2d array, for example, the water, mouse, cat, bridge, and island placements
{


	for (int i = 0; i < n; i++)  //here we set the whole array to island
	{
		for (int j = 0; j < n; j++)
		{
			arr[i][j] = char(32);
		}
	}
	for (int i = 0; i < n; i++) //here we set the boarders of the array to water
	{
		arr[0][i] = char(219);
		arr[n - 1][i] = char(219);
		arr[i][0] = char(219);
		arr[i][n - 1] = char(219);
	}
	
	arr[n / 2][n - 1] = char(175); //here we set the bridge to safety
	arr[n / 2][n / 2] = '*'; //here we set the stating position of the mouse
	a = n / 2;
	b = n / 2;

	int r = (rand() % (n - 2 + 1 - 1)) + 1;  //here we randomize the cat placement
	int c = (rand() % (n - 2 + 1 - 1)) + 1;
	arr[r][c] = '!';  //that's the sign of the cat
	Cat = arr[r][c];

	return(a, b);
}

void Clear_Screen(char arr[][80])  //here we make the 2d array which will include the island 
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			arr[i][j] = ' ';
		}
	}

}

void Display_Scene(char a[][80], char b[][o], int n)  //here we put the island into the big 2d array and display the scene 
{


	for (int i = 0; i < n; i++)  // including the island into the array
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = b[i][j];
		}
	}


	for (int i = 0; i < n; i++) // displaying the whole array on screen
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j];
		}
		cout << endl;
	}
	cout << endl;

}

int Move_Mouse(int& r, int& c)  //here we randomize the mouse movements on the island
{

	int RN = rand() % 4;
	if (RN == 0)
	{
		r--; // goes north
	}
	if (RN == 1)
	{
		c++;  // goes east
	}
	if (RN == 2)
	{
		r++;  //goes south
	}
	if (RN == 3)
	{
		c--; //goes west
	}
	return(r, c);
}




int main()
{
	int rmax; //here we declare the amount of times the game will be repeated
	int size;
	cout << "Enter the size of the island (an odd number and between 7 and 25): ";  //here we ask the user input for the amount of runs and the size of the island and we run checks on the numbers
	cin >> size;
	if ((size % 2 == 0) || (size > 25) || (size < 7))
	{
		do
		{
			cout << "Please, only enter an odd number between 7 and 25: ";
			cin >> size;
		} while ((size % 2 == 0) || (size > 25) || (size < 7));
	}
	cout << "Enter the amount of attempts the mouse will make to escape the island (Game is repeated): ";
	cin >> rmax;
	if (rmax < 0)
	{
		do
		{
			cout << "Please enter a valid number: ";
			cin >> rmax;
		} while (rmax < 0);
	}
	srand(time(NULL));
	char A[o][o];  // here we initalize the arrays to be changed later by the functions as explained above.
	char S[25][80];
	Clear_Screen(S);

	int runs, died, escaped, drowned, starvation;   //here we declare the amount of runs the game was played, and the amount of times the mouse either died, escaped, or dronwed.
	  
	runs = died = escaped = drowned = 0; // here we initalize the runs to zero and the mouse behaviors to zero before the game starts
	starvation = 100;  // here we set the limit of movements afterwards the mouse will die
	char cat = ' ';  //here we initalize the cat to be changed later by the function
	int R = 0; int C = 0; //here we initalize the mouse location to be changed later by the function
	int attempt = 0;  //here we initalize the attempts made
	do   //here we repeat the game as many times as we set rmax to, and we put the initalized variables into the functions to be changed as explained in each function above.
	{
		Initialise_Scene(A, R, C, cat, size); runs++;

		Display_Scene(S, A, size);

		int moves = 0;
		bool finished = false;

		while (!finished)
		{

			Display_Scene(S, A, size);  //here we constantly display an updated array of the mouse moving on the island untill the attempt end.
			A[R][C] = char(32); //here we change the old location of the mouse to a normal place on the island
			Move_Mouse(R, C);

			char temp = A[R][C];  //here we run a check if the location the mouse will be in is hazard or safe which will be used in the if statements below to see if the mouse lives


			A[R][C] = '*';  //here we move the mouse to the new location
			moves++;
			if (temp == char(219)) // if the new mouse location is water then he drowns
			{
				drowned++; finished = true;
			}
			else {
				if (A[R][C] == A[size / 2][size - 1]) // if the new mouse location is the bridge then he escapes
				{
					escaped++; finished = true;
				}
				else
				{
					if (temp == '!' || moves > 100) // if the new mouse location is the cat then he dies
					{
						died++; finished = true;
					}
				}
			}

		}
		attempt++;
		cout << "Moves done in attempt #" << attempt << " = " << moves << endl << endl << endl;  //here we display the moves done by the mouse in each attempt
	} while (runs < rmax);

	cout << "Mouse drowned: " << drowned << " times.\n";  //here we display the results of the game from the attempts done
	cout << "Mouse escaped: " << escaped << " times.\n";
	cout << "Mouse died: " << died << " times.\n";
	system("pause");
	return 0;
}


