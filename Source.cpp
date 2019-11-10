#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>

using namespace std;

struct cell
{
	int posX;
	int posY;
	bool visited;
	bool NWall = true;
	bool SWall = true;
	bool EWall = true;
	bool WWall = true;


	bool checkNeighbor(int width, int height, cell maze[][10], vector<cell> &unvisitedCells)
	{
		if ((posX + 1) > (width - 1))
		{
		}
		else if (maze[posX + 1][posY].visited == false)
		{
			unvisitedCells.push_back(maze[posX + 1][posY]);

		}
		if ((posX - 1) < 0)
		{
		}
		else if (maze[posX - 1][posY].visited == false)
		{
			unvisitedCells.push_back(maze[posX-1][posY]);
		}
		if ((posY + 1) > (height - 1))
		{
		}
		else if (maze[posX][posY + 1].visited == false)
		{
			unvisitedCells.push_back(maze[posX][posY+1]);
		}
		if ((posY - 1) < 0)
		{
		}
		else if (maze[posX][posY - 1].visited == false)
		{
			unvisitedCells.push_back(maze[posX][posY-1]);
		}

		if (unvisitedCells.size() > 0)
		{
			return true;
		}
		else if (unvisitedCells.size() == 0)
		{
			return false;
		}
	}

};

int generateRandomNumber(int limit)			//generates a random number between the ranges of 0 and a specified limit
{
	return (rand() % limit);
}

void initializeMaze(int width, int height, cell maze[][10])
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			maze[x][y].posX = x;
			maze[x][y].posY = y;
			maze[x][y].visited = false;
		}
	}
}

void drawMaze(int width, int height, cell maze[][10])
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (maze[x][y].visited == true)
			{
				cout << "X";
			}
			else if (maze[x][y].visited == false)
			{
				cout << "o";
			}
		}
		cout << endl;
	}
}


int main()
{
	//seed random number generator 
	srand(time(NULL));
	//variables
	int randIndex;							//Variable holds random number generated for use as an index
	int curPosX;
	int curPosY;
	const int width = 10;
	const int height = 10;
	vector <cell> unvisitedCell;			//holds the unvisited cells that are around the current cell
	stack <cell> backTrack;					//stack is used to facilitate backtracking
	cell grid[width][height];

	//initialize the maze
	initializeMaze(width, height, grid);

	//step 1: pick random number from grid and make that the current  
	curPosX = generateRandomNumber(width);
	curPosY = generateRandomNumber(height);
	backTrack.push(grid[curPosX][curPosY]);
	grid[curPosX][curPosY].visited = true;

	//do while there are unvisited cells
	while (backTrack.size() > 0)
	{
		
		cout << "curPosX: " << curPosX << ", curPosY: " << curPosY <<endl;
		drawMaze(width, height, grid);
		
		if (grid[curPosX][curPosY].checkNeighbor(width, height, grid, unvisitedCell) == true)
		{
			//pick random unvisited cell
			

			if (unvisitedCell.size() > 1)
			{
				randIndex = generateRandomNumber(unvisitedCell.size());

			}
			else
			{
				randIndex = 0;
			}

			if (unvisitedCell.size() > 1)
			{
				backTrack.push(grid[curPosX][curPosY]);
			}

			//removing walls between the current cell and chosen neighbor cell
			if (((curPosX - unvisitedCell.at(randIndex).posX) == 1) || ((curPosX - unvisitedCell.at(randIndex).posX) == -1))
			{
				switch (curPosX - unvisitedCell.at(randIndex).posX)			
				{
				case 1:	//	WEST
					//break walls
					grid[curPosX][curPosY].WWall = false;
					grid[curPosX-1][curPosY].EWall = false;
					//set new x/y values for current cell
					curPosX = curPosX - 1;
					//mark the new cell as visited
					grid[curPosX][curPosY].visited = true;
					break;
				case -1: // EAST
					grid[curPosX][curPosY].EWall = false;
					grid[curPosX+1][curPosY].WWall = false;
					//set new x/y values for current cell
					curPosX = curPosX + 1;
					//mark the new cell as visited
					grid[curPosX][curPosY].visited = true;
					break;
				}
			}
			else if (((curPosY - unvisitedCell.at(randIndex).posY) == 1) || ((curPosY - unvisitedCell.at(randIndex).posY) == -1))
			{
				switch (curPosY - unvisitedCell.at(randIndex).posY)
				{
				case 1: //NORTH
					grid[curPosX][curPosY].NWall = false;
					grid[curPosX][curPosY-1].SWall = false;
					//set new x/y values for current cell
					curPosY = curPosY - 1;
					//mark the new cell as visited
					grid[curPosX][curPosY].visited = true;
					break;
				case -1: //SOUTH
					grid[curPosX][curPosY].SWall = false;
					grid[curPosX][curPosY + 1].NWall = false;
					//set new x/y values for current cell
					curPosY = curPosY + 1;
					//mark the new cell as visited
					grid[curPosX][curPosY].visited = true;
					break;
				}
			}
			
			//upgrade the chosen cell to the new current cell and mark it as visited
			unvisitedCell.clear();
			
			
		}
		else if (grid[curPosX][curPosY].checkNeighbor(width, height, grid, unvisitedCell) == false)
		{
			cout << "BACKTRACK ENGAGED: " << " curPosX: " << curPosX << ", curPosY: " << curPosY << endl;
			
			do 
			{
				curPosX = backTrack.top().posX;
				curPosY = backTrack.top().posY;
				cout << "curPosX: " << curPosX << ", curPosY: " << curPosY << endl;
				backTrack.pop();
				unvisitedCell.clear();
			} while ((backTrack.size() != 0) && (backTrack.top().checkNeighbor(width, height, grid, unvisitedCell) == false));
		}
	}
	cout << "all cells visited" << endl;
	drawMaze(width, height, grid);

	return 0;
}


