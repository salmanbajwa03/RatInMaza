#include<iostream>
#include<fstream>

using namespace std;

const int GridSize = 4; //Globally !


template <typename T>

class Stack
{
	T *arr;
	int currentIndex;
	int size = 0;
public:

	Stack() //Constructor
	{
		size = 100;
		arr = new T[size];
		currentIndex = -1;
	}
	~Stack() //Destructor
	{
		delete[]arr;
	}

	bool IsFull()
	{
		if (currentIndex == size - 1)
		{
			return true;
		}
		return false;
	}

	bool IsEmpty()
	{
		if (currentIndex == -1)
		{
			return true;
		}
		return false;
	}

	void Push(T number)
	{
		if (IsFull() == false)
		{
			currentIndex++;
			arr[currentIndex] = number;
		}
		else
			cout << "ARRAY IS FULL " << endl;
	}

	void Pop()
	{
		if (IsEmpty() == false)
			currentIndex--;
		else
			cout << " ARRAY IS EMPTY  " << endl;
	}



	T Top()
	{
		return arr[currentIndex];
	}
	T returnCurrentIndex()
	{
		return CurrentIndex;
	}



};






void takeInput(int maze[][GridSize], const int GridSize)
{
	ifstream fin("maze.txt");
	if (!fin)
	{
		cout << "File couldn't opened !! ";
		exit(true);
	}
	for (int i = 0; i < GridSize; i++)
	{
		for (int j = 0; j < GridSize; j++)
		{
			fin >> maze[i][j];
		}
	}

}
bool isWin(int maze[][GridSize],int GridSize)

{
	if (maze[GridSize - 1][GridSize - 1]==2)
	{
		return true;
	}
	else
		return false;

}

void findRat(int maze[][GridSize],int GridSize,int & Sr,int & Sc)
{
	for (int i = 0; i < GridSize; i++)
	{
		for (int j = 0; j < GridSize; j++)
		{
			if (maze[i][j] == 2)
			{

				Sr = i;
				Sc = j;
				return;
			}
		}
	}
}


bool moveRight(int maze[][GridSize], int GridSize, int Sr, int Sc, int Dr, int Dc, Stack <char> & obj)
{
	if (maze[Dr][Dc] == 0)
	{
		return false;
	}

	if (maze[Dr][Dc] == -1)
	{
		return false;
	}

	 if (maze[Dr][Dc] == 1)
	{
		 obj.Push('R');
		maze[Dr][Dc] = 2;
		maze[Sr][Sc] = 1;
		return true;
	}
	 return false;
}

bool moveLeft(int maze[][GridSize], int GridSize, int Sr, int Sc, int Dr, int Dc, Stack <char> & obj)
{
	if (maze[Dr][Dc] == 0)
	{
		return false;
	}

	

	 if (maze[Dr][Dc] == 1)
	{
		 obj.Push('L');
		maze[Dr][Dc] = 2;
		maze[Sr][Sc] = -1;
		return true;
	}
	 return false;
}

bool moveUp(int maze[][GridSize], int GridSize, int Sr, int Sc, int Dr, int Dc, Stack <char> & obj)
{
	if (maze[Dr][Dc] == 0)
	{
		return false;
	}

	
	 if (maze[Dr][Dc] == 1)
	{
		 obj.Push('U');
		maze[Dr][Dc] = 2;
		maze[Sr][Sc] = 1;
		return true;
	}
	 return false;
}

bool moveDown(int maze[][GridSize], int GridSize, int Sr, int Sc, int Dr, int Dc, Stack <char> & obj)
{
	if (maze[Dr][Dc] == 0)
	{
		return false;
	}

	

	else if (maze[Dr][Dc] == 1)
	{
		obj.Push('D');
		maze[Dr][Dc] = 2;
		maze[Sr][Sc] = 1;
		return true;
	}
	return false;
}

void PrintMaze(int maze[][GridSize], int GridSize)
{
	cout << endl;
	for (int i = 0; i < GridSize; i++)
	{
		for (int j = 0; j < GridSize; j++)
		{
			cout << maze[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()


{
	int maze[GridSize][GridSize];
	int Sr, Sc = 0;
	takeInput(maze, GridSize);

	Stack <char> obj;

	while (!isWin(maze, GridSize))
	{		
		PrintMaze(maze, GridSize);
		bool Moved = false;
		findRat(maze, GridSize, Sr, Sc);
		Moved=moveRight(maze,GridSize,Sr,Sc,Sr,Sc+1,obj);
		if (!Moved)
		{
			Moved = moveDown(maze, GridSize, Sr, Sc, Sr+1, Sc,obj);
			if (!Moved)
			{
				Moved = moveUp(maze, GridSize, Sr, Sc, Sr-1, Sc,obj );
				if (!Moved)
				{
					Moved = moveLeft(maze, GridSize, Sr, Sc, Sr , Sc- 1,obj);
					if (!Moved)
					{
						cout << "Ops Stuck !!! ";
						exit(true);
					}
				}
			}
			
		}
	}
	PrintMaze(maze, GridSize);
	cout << endl << endl;
	char dummy[10];
	int i = 0;
	while (!obj.IsEmpty())
	{
		dummy[i] = obj.Top();
		obj.Pop();
		i++;
	}
	dummy[i] = '/0';
	
	

	for (int j = i - 1; j >= 0; j--)
		cout << dummy[j] << " ";
	
	
	return 0;
}
