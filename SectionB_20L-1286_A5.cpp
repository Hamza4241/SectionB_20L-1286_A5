#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------------
//Q1 starts here.

int StringLength(char temp_buffer[20]) //String Length of static char array
{
	int StrLength = 0;
	for (int i = 0; temp_buffer[i] != '\0'; i++)
	{
		StrLength++;
	}
	return StrLength;
}

char** GetStringFromBuffer(char temp_words[20][20], const int totalWords) //Putting words from temp array to our dynammic char array
{
	char** words = new char*[totalWords];
	for (int i = 0; i < totalWords; i++)
	{
		int StrLength = StringLength(temp_words[i]);
		words[i] = new char[StrLength+1];
		int j;
		for (j = 0; j < StrLength; j++)
		{
			words[i][j] = temp_words[i][j];
		}
		words[i][j] = '\0';
	}
	return words;
}

char** ReadDataFromFile(int &totalWords) //Reads data from file and saves it in temp static array.
{
	cout << "Please enter the full name of the file with extension(example '.txt') which contains your words: ";
	char File_Name[20];
	cin >> File_Name;

	ifstream input_names(File_Name);
	if (!input_names.is_open())
	{
		cout << "\nError!\nFile couldn't be opened\n\n";
		return 0;
	}
	else
		cout << "\n" << File_Name << " opened successfully\n\n";

	cout << "Enter total number of words you want to use(max limit is 10): ";
	cin >> totalWords;
	cout << endl << "List of Word(s) that will be considered: " << endl << endl;
		
	char temp_words[20][20]; //Initially saves the words in this array from file
	for (int i = 0; i < totalWords; i++)
	{
		char temp_buffer[20];
		input_names.getline(temp_buffer, 20);
		int j;
		for (j = 0; temp_buffer[j] != '\0'; j++)
		{
			temp_words[i][j] = temp_buffer[j];
		}
		temp_words[i][j] = '\0';
	}
	input_names.close();
	char** words = GetStringFromBuffer(temp_words, totalWords);
	return words;
}

int StrLengthOfPointer(char* temp) //String Length of dynamic char array
{
	int Length = 0;
	for (int i = 0; temp[i] != '\0'; i++)
	{
		if (temp[i] != ' ')
			Length++;
		else
			continue;
	}
	return Length;
}

int SearchForBiggestWord(char** words, const int totalWords) //To get length of biggest word 
{
	int BiggestLength = 0;
	for (int i = 0; i < totalWords; i++)
	{
		int Length = StrLengthOfPointer(words[i]);
		if (Length >= BiggestLength)
		{
			BiggestLength = Length;
		}
	}
	return BiggestLength;
}

inline void Downward(int &LengthOfWord, int &i, int &j, int &word, int& ROWS, int &FLAG, char** words, char** Grid) //Downward direction
{
	int downward_limit = i + LengthOfWord;
	if (downward_limit < ROWS && FLAG != 1)
	{
		for (int row = i + 1, col = j, k = 1; row < downward_limit; row++, k++) // k controls the alphabets of the word from our list
		{
			if (Grid[row][col] == '-' || Grid[row][col] == (int)words[word][k] - 32)
			{
				FLAG = 0;
				if (row == downward_limit - 1 && FLAG == 0)
				{
					for (int a = i, b = j, z = 0; a < downward_limit; a++, z++) // a and b represent rows and columns of grid where z represents alphbets from our list of words
					{
						if (words[word][z] != ' ')
						{
							if ((int)words[word][z] > 96)
								Grid[a][b] = (int)words[word][z] - 32;
							else
								Grid[a][b] = words[word][z];
							if (a == downward_limit - 1)
								FLAG = 1;
						}
						else
						{
							a = a - 1;
						}
					}
				}

			}
			else
				break;
		}
	}
}

inline void Upward(int &LengthOfWord, int &i, int &j, int &word, int &FLAG, char** words, char** Grid) //Upward Direction
{
	int upward_limit = i - LengthOfWord;
	if (upward_limit >= 0 && FLAG != 1)
	{
		for (int row = i - 1, col = j, k = 1; row > upward_limit; row--, k++) // k controls the alphabets of the word from our list
		{
			if (Grid[row][col] == '-' || Grid[row][col] == (int)words[word][k] - 32)
			{
				FLAG = 0;
				if (row == upward_limit + 1 && FLAG == 0)
				{
					for (int a = i, b = j, z = 0; a > upward_limit; a--, z++) // // a and b represent rows and columns of grid where z represents alphbets from our list of words
					{
						if (words[word][z] != ' ')
						{
							if ((int)words[word][z] > 96)
								Grid[a][b] = (int)words[word][z] - 32;
							else
								Grid[a][b] = words[word][z];
							if (a == upward_limit + 1)
								FLAG = 1;
						}
						else
						{
							a = a + 1;
						}
					}
				}

			}
			else
				break;
		}
	}
}

inline void Rightward(int& LengthOfWord, int& i, int& j, int& word, int& COLS, int& FLAG, char** words, char** Grid) //Right Direction 
{
	int rightward_limit = j + LengthOfWord;
	if (rightward_limit < COLS && FLAG != 1)
	{
		for (int row = i, col = j + 1, k = 1; col < rightward_limit; col++, k++) // k controls the alphabets of the word from our list
		{
			if (Grid[row][col] == '-' || Grid[row][col] == (int)words[word][k] - 32)
			{
				FLAG = 0;
				if (col == rightward_limit - 1 && FLAG == 0)
				{
					for (int a = i, b = j, z = 0; b < rightward_limit; b++, z++) // a and b represent rows and columns of grid where z represents alphbets from our list of words
					{
						if (words[word][z] != ' ')
						{
							if ((int)words[word][z] > 96)
								Grid[a][b] = (int)words[word][z] - 32;
							else
								Grid[a][b] = words[word][z];
							if (b == rightward_limit - 1)
								FLAG = 1;
						}
						else
						{
							b = b - 1;
						}
					}
				}

			}
			else
				break;
		}
	}
}

inline void Leftward(int& LengthOfWord, int& i, int& j, int& word, int& FLAG, char** words, char** Grid) //Left Direction
{
	int leftward_limit = j - LengthOfWord;
	if (leftward_limit >= 0 && FLAG != 1)
	{
		for (int row = i, col = j - 1, k = 1; col > leftward_limit; col--, k++) // k controls the alphabets of the word from our list
		{
			if (Grid[row][col] == '-' || Grid[row][col] == (int)words[word][k] - 32)
			{
				FLAG = 0;
				if (col == leftward_limit + 1 && FLAG == 0)
				{
					for (int a = i, b = j, z = 0; b > leftward_limit; b--, z++) // a and b represent rows and columns of grid where z represents alphbets from our list of words
					{
						if (words[word][z] != ' ')
						{
							if ((int)words[word][z] > 96)
								Grid[a][b] = (int)words[word][z] - 32;
							else
								Grid[a][b] = words[word][z];
							if (b == leftward_limit + 1)
								FLAG = 1;
						}
						else
						{
							b = b + 1;
						}
					}
				}

			}
			else
				break;
		}
	}
}

inline void TopLeft(int& LengthOfWord, int& i, int& j, int& word, int& FLAG, char** words, char** Grid) //Top Left Direction
{
	int upward_limit = i - LengthOfWord;
	int leftward_limit = j - LengthOfWord;
	if (leftward_limit >= 0 && upward_limit >= 0 && FLAG != 1)
	{
		for (int row = i - 1, col = j - 1, k = 1; col > leftward_limit && row > upward_limit; col--, row--, k++) // k controls the alphabets of the word from our list
		{
			if (Grid[row][col] == '-' || Grid[row][col] == (int)words[word][k] - 32)
			{
				FLAG = 0;
				if (col == leftward_limit + 1 && row == upward_limit + 1 && FLAG == 0)
				{
					for (int a = i, b = j, z = 0; b > leftward_limit && a > upward_limit; a--, b--, z++) // a and b represent rows and columns of grid where z represents alphbets from our list of words
					{
						if (words[word][z] != ' ')
						{
							if ((int)words[word][z] > 96)
								Grid[a][b] = (int)words[word][z] - 32;
							else
								Grid[a][b] = words[word][z];
							if (b == leftward_limit + 1 && a == upward_limit + 1)
								FLAG = 1;
						}
						else
						{
							a = a + 1;
							b = b + 1;
						}
					}
				}

			}
			else
				break;
		}
	}
}

inline void TopRight(int& LengthOfWord, int& i, int& j, int& word, int& COLS, int& FLAG, char** words, char** Grid) //Top Right Direction
{
	int upward_limit = i - LengthOfWord;
	int rightward_limit = j + LengthOfWord;
	if (rightward_limit < COLS && upward_limit >= 0 && FLAG != 1)
	{
		for (int row = i - 1, col = j + 1, k = 1; col < rightward_limit && row > upward_limit; col++, row--, k++) // k controls the alphabets of the word from our list
		{
			if (Grid[row][col] == '-' || Grid[row][col] == (int)words[word][k] - 32)
			{
				FLAG = 0;
				if (col == rightward_limit - 1 && row == upward_limit + 1 && FLAG == 0)
				{
					for (int a = i, b = j, z = 0; b < rightward_limit && a > upward_limit; a--, b++, z++) // a and b represent rows and columns of grid where z represents alphbets from our list of words
					{
						if (words[word][z] != ' ')
						{
							if ((int)words[word][z] > 96)
								Grid[a][b] = (int)words[word][z] - 32;
							else
								Grid[a][b] = words[word][z];
							if (b == rightward_limit - 1 && a == upward_limit + 1)
								FLAG = 1;
						}
						else
						{
							a = a + 1;
							b = b - 1;
						}
					}
				}

			}
			else
				break;
		}
	}
}

inline void BottomLeft(int& LengthOfWord, int& i, int& j, int& word, int& ROWS, int& FLAG, char** words, char** Grid) //Bottom Left Direction
{
	int leftward_limit = j - LengthOfWord;
	int downward_limit = i + LengthOfWord;
	if (leftward_limit >= 0 && downward_limit < ROWS && FLAG != 1)
	{
		for (int row = i + 1, col = j - 1, k = 1; col > leftward_limit && row < downward_limit; col--, row++, k++) // k controls the alphabets of the word from our list
		{
			if (Grid[row][col] == '-' || Grid[row][col] == (int)words[word][k] - 32)
			{
				FLAG = 0;
				if (col == leftward_limit + 1 && row == downward_limit - 1 && FLAG == 0)
				{
					for (int a = i, b = j, z = 0; b > leftward_limit && a < downward_limit; a++, b--, z++) // a and b represent rows and columns of grid where z represents alphbets from our list of words
					{
						if (words[word][z] != ' ')
						{
							if ((int)words[word][z] > 96)
								Grid[a][b] = (int)words[word][z] - 32;
							else
								Grid[a][b] = words[word][z];
							if (b == leftward_limit + 1 && a == downward_limit - 1)
								FLAG = 1;
						}
						else
						{
							a = a - 1;
							b = b + 1;
						}
					}
				}

			}
			else
				break;
		}
	}
}

inline void BottomRight(int& LengthOfWord, int& i, int& j, int& word, int& ROWS, int& COLS, int& FLAG, char** words, char** Grid) //Bottom Right Direction
{
	int rightward_limit = j + LengthOfWord;
	int downward_limit = i + LengthOfWord;
	if (rightward_limit < COLS && downward_limit < ROWS && FLAG != 1)
	{
		for (int row = i + 1, col = j + 1, k = 1; col < rightward_limit && row < downward_limit; col++, row++, k++) // k controls the alphabets of the word from our list
		{
			if (Grid[row][col] == '-' || Grid[row][col] == (int)words[word][k] - 32)
			{
				FLAG = 0;
				if (col == rightward_limit - 1 && row == downward_limit - 1 && FLAG == 0)
				{
					for (int a = i, b = j, z = 0; b < rightward_limit && a < downward_limit; a++, b++, z++) // a and b represent rows and columns of grid where z represents alphbets from our list of words
					{
						if (words[word][z] != ' ')
						{
							if ((int)words[word][z] > 96)
								Grid[a][b] = (int)words[word][z] - 32;
							else
								Grid[a][b] = words[word][z];
							if (b == rightward_limit - 1 && a == downward_limit - 1)
								FLAG = 1;
						}
						else
						{
							a = a - 1;
							b = b - 1;
						}
					}
				}

			}
			else
				break;
		}
	}
}

inline void PlaceRandomAlphabets(int& ROWS, int& COLS, char** Grid) //Places random alphabets in the remaining directions
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (Grid[i][j] == '-')
			{
				int number = 0;
				number = (rand() % 25) + 65;
				Grid[i][j] = number;
			}
		}
	}
}

inline void OutputToFile(int& ROWS, int& COLS, char** Grid) //Saves the newly created grid in the file
{
	cout << "Enter the full name of the file where you want to place your newly created grid: ";
	char File_Name[20];
	cin >> File_Name;
	ofstream out(File_Name);

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			out << Grid[i][j] << "  ";
		}
		out << endl;
	}
	out.close();
	cout << "\nCONGRATULATION! Grid successfully created and saved in the file " << File_Name << endl << endl;
}

void CreatingGrid(char** words, const int totalWords) //Creates grid according to given rows and cols, and places words in it.
{
	int ROWS;
	int COLS;
	cout << "\n\nEnter rows of your Grid: ";
	cin >> ROWS;
	cout << "Enter columns of your Grid: ";
	cin >> COLS;
	cout << endl;
	cout << endl;

	int LengthOfBiggestWord = SearchForBiggestWord(words, totalWords);
	if (LengthOfBiggestWord > ROWS && LengthOfBiggestWord > COLS)
	{
		cout << "Grid cannot be formed, Size of Gird too small to contain the bigget word\n";
		return;
	}

	char** Grid = new char* [ROWS]; // Creating Grid on Heap
	for (int i = 0; i < ROWS; i++)
		Grid[i] = new char[COLS];

	for (int i = 0; i < ROWS; i++) //Initilizing all places of Grid to "-" dash character
	{
		for (int j = 0; j < COLS; j++)
		{
			Grid[i][j] = '-';
		}
	}

	for (int word = 0; word < totalWords; word++)
	{
		int FLAG = 0; //To check weather word is placed on grid or not

		while (FLAG != 1)
		{
			srand((unsigned) time(NULL)); //Randomly generates numbers
			int i, j;
			i = (rand() % ROWS); //Random number for row
			j = (rand() % COLS); //Random number for col

			if (Grid[i][j] == '-' || Grid[i][j] == words[word][0])
			{
				int LengthOfWord = StrLengthOfPointer(words[word]);

				TopLeft(LengthOfWord, i, j, word, FLAG, words, Grid);
				TopRight(LengthOfWord, i, j, word, COLS, FLAG, words, Grid);
				BottomLeft(LengthOfWord, i, j, word, ROWS, FLAG, words, Grid);
				BottomRight(LengthOfWord, i, j, word, ROWS, COLS, FLAG, words, Grid);

				Downward(LengthOfWord, i, j, word, ROWS, FLAG, words, Grid);
				Upward(LengthOfWord, i, j, word, FLAG, words, Grid);
				Rightward(LengthOfWord, i, j, word, COLS, FLAG, words, Grid);
				Leftward(LengthOfWord, i, j, word, FLAG, words, Grid);
			}
		}
	}
//-------------------------------------------------------------------------------------------------------------
	PlaceRandomAlphabets(ROWS, COLS, Grid);
//---------------------------------------------------------------------------------------------------------- Output to file begins
	OutputToFile(ROWS, COLS, Grid);

	for (int i = 0; i < ROWS; i++)
		delete[] Grid[i];
	delete[] Grid;
}


//Q1 ends here.
//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------
//Q2 starts here.


char** InputGrid(int& rows, int& cols) //Takes grid from File and saves it in char**
{

	char** Grid = new char* [rows];
	for (int i = 0; i < rows; i++)
		Grid[i] = new char[cols];

	cout << "Enter the name of the file including format(.txt) which contains the grid for Search String: ";
	char File_Name[20];
	cin >> File_Name;
	ifstream fin(File_Name);
	if (!fin.is_open())
	{
		cout << "\nError!\nFile couldn't be opened\n\n";
		return 0;
	}
	else
		cout << "\n" << File_Name << " opened successfully\n\n";

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			fin >> Grid[i][j];
		}
	}
	fin.close();
	return Grid;
}

char** InputWords(int& WordCount, int& rows, int& cols) //Takes words from the given file
{

	cout << "Enter the name of the file which contains the words to be searched from Grid: ";
	char File_Name[20];
	cin >> File_Name;
	ifstream InputData(File_Name);
	if (!InputData.is_open())
	{
		cout << "\nError!\nFile couldn't be opened\n\n";
		return 0;
	}
	else
		cout << "\n" << File_Name << " opened successfully\n\n";

	InputData >> rows;
	InputData >> cols;

	InputData >> WordCount;
	char** Words = new char* [WordCount];

	for (int i = 0; i < WordCount; i++)
	{
		char tempBuffer[20];
		InputData >> tempBuffer;
		int Length = StringLength(tempBuffer);

		Words[i] = new char[Length + 1];

		int j;
		for (j = 0; j < Length; j++)
		{
			Words[i][j] = tempBuffer[j];
		}
		Words[i][j] = '\0';
	}
	InputData.close();

	return Words;
}

inline int Upward(char* Word, char** Grid, int& Lenght, int& i, int& j, ofstream& out) //To check in upward direction
{
	int upward_limit = i - Lenght;
	if (upward_limit >= 0)
	{
		for (int row = i - 1, col = j, k = 1; row > upward_limit; row--, k++) 
		{
			if (Grid[row][col] == Word[k])
			{
				if (row == upward_limit + 1)
				{
					out << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					cout << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					return 0;
				}
			}
			else
				return 1;
		}
	}
	return 1;
}

inline int Downward(char* Word, char** Grid, int& rows, int& Lenght, int& i, int& j, ofstream& out) //To check in downward direction
{
	int downward_limit = i + Lenght;
	if (downward_limit < rows)
	{
		for (int row = i + 1, col = j, k = 1; row < downward_limit; row++, k++)
		{
			if (Grid[row][col] == Word[k])
			{
				if (row == downward_limit - 1)
				{
					out << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					cout << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					return 0;
				}
			}
			else
				return 1;
		}
	}
	return 1;
}

inline int Rightward(char* Word, char** Grid, int& cols, int& Lenght, int& i, int& j, ofstream& out) //To check in rightward direction
{
	int rightward_limit = j + Lenght;
	if (rightward_limit < cols)
	{
		for (int row = i, col = j + 1, k = 1; col < rightward_limit; col++, k++)
		{
			if (Grid[row][col] == Word[k])
			{
				if (col == rightward_limit - 1)
				{
					out << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					cout << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					return 0;
				}
			}
			else
				return 1;
		}
	}
	return 1;
}

inline int Leftward(char* Word, char** Grid, int& Lenght, int& i, int& j, ofstream& out) //To check in leftward direction
{
	int leftward_limit = j - Lenght;
	if (leftward_limit >= 0)
	{
		for (int row = i, col = j - 1, k = 1; col > leftward_limit; col--, k++)
		{
			if (Grid[row][col] == Word[k])
			{
				if (col == leftward_limit + 1)
				{
					out << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					cout << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					return 0;
				}
			}
			else
				return 1;
		}
	}
	return 1;
}

inline int TopLeft(char* Word, char** Grid, int& Lenght, int& i, int& j, ofstream& out)  //To check in top left direction
{
	int leftward_limit = j - Lenght;
	int upward_limit = i - Lenght;
	if (leftward_limit >= 0 && upward_limit >= 0)
	{
		for (int row = i - 1, col = j - 1, k = 1; col > leftward_limit && row > upward_limit; col--, row--, k++)
		{
			if (Grid[row][col] == Word[k])
			{
				if (col == leftward_limit + 1 && row == upward_limit + 1)
				{
					out << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					cout << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					return 0;
				}
			}
			else
				return 1;
		}
	}
	return 1;
}

inline int TopRight(char* Word, char** Grid, int& cols, int& Lenght, int& i, int& j, ofstream& out) //To check in top right direction
{
	int rightward_limit = j + Lenght;
	int upward_limit = i - Lenght;
	if (rightward_limit < cols && upward_limit >= 0)
	{
		for (int row = i - 1, col = j + 1, k = 1; col < rightward_limit && row > upward_limit; col++, row--, k++)
		{
			if (Grid[row][col] == Word[k])
			{
				if (col == rightward_limit - 1 && row == upward_limit + 1)
				{
					out << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					cout << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					return 0;
				}
			}
			else
				return 1;
		}
	}
	return 1;
}

inline int BottomRight(char* Word, char** Grid, int& cols, int& rows, int& Lenght, int& i, int& j, ofstream& out) //To check in bottom right direction
{
	int rightward_limit = j + Lenght;
	int downward_limit = i + Lenght;
	if (rightward_limit < cols && downward_limit < rows)
	{
		for (int row = i + 1, col = j + 1, k = 1; col < rightward_limit && row < downward_limit; col++, row++, k++)
		{
			if (Grid[row][col] == Word[k])
			{
				if (col == rightward_limit - 1 && row == downward_limit - 1)
				{
					out << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					cout << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					return 0;
				}
			}
			else
				return 1;
		}
	}
	return 1;
}

inline int BottomLeft(char* Word, char** Grid, int& rows, int& Lenght, int& i, int& j, ofstream& out) //To check in bottom left direction
{
	int leftward_limit = j - Lenght;
	int downward_limit = i + Lenght;
	if (leftward_limit >= 0 && downward_limit < rows)
	{
		for (int row = i + 1, col = j - 1, k = 1; col > leftward_limit && row < downward_limit; col--, row++, k++)
		{
			if (Grid[row][col] == Word[k])
			{
				if (col == leftward_limit + 1 && row == downward_limit - 1)
				{
					out << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					cout << "{" << i << "," << j << "}{" << row << "," << col << "}" << endl << endl;
					return 0;
				}
			}
			else
				return 1;
		}
	}
	return 1;
}

int SearchWord(char** Grid, char* Word, int rows, int cols, ofstream& out) //Calls functions to check if the word is available in the grid
{
	int Lenght = StrLengthOfPointer(Word);
	int i, j;
	int Word_Found = 1;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (Word[0] == Grid[i][j])
			{
				//Upward Directiom
				Word_Found = Upward(Word, Grid, Lenght, i, j, out);
				if (Word_Found == 0)
					return 0;
				//-------------------------------------------------------------------------------------------------------
				//Downward Direction
				Word_Found = Downward(Word, Grid, rows, Lenght, i, j, out);
				if (Word_Found == 0)
					return 0;
				//-------------------------------------------------------------------------------------------------------
				//Right Direction
				Word_Found = Rightward(Word, Grid, cols, Lenght, i, j, out);
				if (Word_Found == 0)
					return 0;
				//-------------------------------------------------------------------------------------------------------
				//Left direction
				Word_Found = Leftward(Word, Grid, Lenght, i, j, out);
				if (Word_Found == 0)
					return 0;
				//-------------------------------------------------------------------------------------------------------
				//top left direction
				Word_Found = TopLeft(Word, Grid, Lenght, i, j, out);
				if (Word_Found == 0)
					return 0;
				//-------------------------------------------------------------------------------------------------------
				//top right direction
				Word_Found = TopRight(Word, Grid, cols, Lenght, i, j, out);
				if (Word_Found == 0)
					return 0;
				//-------------------------------------------------------------------------------------------------------
				//bottom right direction
				Word_Found = BottomRight(Word, Grid, cols, rows, Lenght, i, j, out);
				if (Word_Found == 0)
					return 0;
				//-------------------------------------------------------------------------------------------------------
				//bottom left direction
				Word_Found = BottomLeft(Word, Grid, rows, Lenght, i, j, out);
				if (Word_Found == 0)
					return 0;
				//-------------------------------------------------------------------------------------------------------
			}
		}
		if (i == rows - 1 && j == cols) //IF the word is not found on the Grid
		{
			out << "Not Found" << endl << endl;
			cout << "Not Found" << endl << endl;
			return 0;
		}
	}
}

//Q2 ends here.
//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------


int main()
{
	int terminate; //To control when to show home screen and when terminate the program
	cout << "Enter any positive number to move to Home Screen, enter negative number to terminate: ";
	cin >> terminate;
	cout << endl << endl;
	while (terminate >= 0)
	{
		cout << "---------------------------------------Welcome to home screen---------------------------------------\n\n";
		cout << "What would you like to perform\n\n";
		cout << "1) Create Grid (Enter C)\n"
			<< "2) Search Words from Grid (Enter S)\n"
			<< "3) Quit (Enter Q)\n";

		cout << "\nEnter your option: ";
		char User_Option;
		cin >> User_Option;
		cout << endl;

		int UserOption = 5;
		if ((int)User_Option == 67 || (int)User_Option == 99) //if option is 'C'
			UserOption = 0;
		else if ((int)User_Option == 83 || (int)User_Option == 115) //if option is 'S'
			UserOption = 1;
		else if ((int)User_Option == 81 || (int)User_Option == 113) //if option is Q
			UserOption = 2;
		else
		{
			cout << "Entered option is not valid\n\n";
			cout << "Enter any positive number to move to Home Screen, enter negative number to terminate: ";
			cin >> terminate;
			cout << endl << endl;
			continue;
		}


		if (UserOption == 0) //When the user wants to create a Grid
		{
			int totalWords = 0;
			char** words = ReadDataFromFile(totalWords);
			if (words == 0)
			{
				cout << "Enter any positive number to move to Home Screen, enter negative number to terminate: ";
				cin >> terminate;
				cout << endl << endl;
				continue;
			}

			for (int i = 0; i < totalWords; i++)
			{
				cout << words[i] << endl;
			}

			CreatingGrid(words, totalWords);

			for (int i = 0; i < totalWords; i++)
			{
				delete[] words[i];
			}
			if (words)
				delete[] words;
		}
		else if (UserOption == 1) //When the user wants to search for words from the grid
		{
			int rows, cols;
			int WordCount;
			char** Words = InputWords(WordCount, rows, cols);

			
			char** Grid = InputGrid(rows, cols);
			if (Grid == 0)
			{
				cout << "Enter any positive number to move to Home Screen, enter negative number to terminate: ";
				cin >> terminate;
				cout << endl << endl;
				continue;
			}

			char File_Name[20];
			cout << "Enter the name of the file where you want to place found word data: ";
			cin >> File_Name;
			cout << endl;
			ofstream out(File_Name);
			for (int i = 0; i < WordCount; i++)
				SearchWord(Grid, Words[i], rows, cols, out);
			out.close();

			for (int i = 0; i < rows; i++)
				delete[] Grid[i];
			delete[] Grid;
			for (int i = 0; i < WordCount; i++)
				delete[] Words[i];
			delete[] Words;
		}
		else if (UserOption == 2) //When the user wants to Quit
		{
			cout << "\nExiting the program.\n\n";
			return 0;
		}
			

		cout << "Enter any positive number to move to Home Screen, enter negative number to terminate: ";
		cin >> terminate;
		cout << endl << endl;
	}

	return 0;
}