#include "DisjSet.hpp"
#include <stdlib.h>
#include <iostream>
#include <time.h>

/*

*/

//using namespace std;


//hardcodes the border conditions of the maze
int getAdjacentCellIndex(int n, int size)
{
  int neighbor, dir;  //look left down right or up?
  bool leftEdge, topEdge, rightEdge, bottomEdge;

  //check for boundary conditions and randomly reassign direction to a valid one
  
  leftEdge = (n % MATRIX_COLS) == 0;
  topEdge = n < MATRIX_COLS;
  rightEdge = (n % MATRIX_COLS) == (MATRIX_COLS - 1);
  bottomEdge = n >= (size - MATRIX_COLS);

  dir = rand() % 4;
  //top left corner
  if(n == 0){
    while(dir == LEFT || dir == UP)
      dir = rand() % 4;    
  }
  //top right corner
  else if(topEdge && rightEdge){
    while(dir == RIGHT || dir == UP)
      dir = rand() % 4;
  }
  //bottom right corner
  else if(bottomEdge && rightEdge){
    while(dir == RIGHT || dir == DOWN)
      dir = rand() % 4;
  }
  //bottom left corner
  else if(bottomEdge && leftEdge){
    while(dir == LEFT || dir == DOWN)
      dir = rand() % 4;
  }
  else if(topEdge){
    while(dir == UP)
      dir = rand() % 4;
  }
  else if(rightEdge){
    while(dir == RIGHT)
      dir = rand() % 4;
  }
  else if(bottomEdge){
    while(dir == DOWN)
      dir = rand() % 4;
  }
  else if(leftEdge){
    while(dir == LEFT)
      dir = rand() % 4;
  }
  //else: random dir will do

  //cout << "dir: " << dir << endl;

  switch(dir){
    case LEFT:
      neighbor = n - 1;
      break;

    case DOWN:
      neighbor = n + COLS;
      break;

    case RIGHT:
      neighbor = n + 1;
      break;

    case UP:
      neighbor = n - COLS;
      break;

    default:
      cout << "SWITCH ERROR" << endl;
      break;
  }

  if(neighbor < 0 || neighbor >= size){
    cout << "neighbor cell out of range: " << neighbor << endl;
    cout << "direction: " << dir << endl;
    exit(0);
  }

  return neighbor;
}

//makes a maze of the 
void makeMaze(DisjSet& maze)
{
  int randomCell, randomNeighbor, i = 0;
  int root1, root2;

  //while the first and last cell are not connected, knock down walls
  while(maze.find(maze.maze[0].i) != maze.find(maze.maze[ maze.maze.size()-1 ].i)){
    //select two random adjacent cells
    randomCell = rand() % maze.maze.size();
    randomNeighbor = getAdjacentCellIndex(randomCell,maze.maze.size());
    //cout << "randomCell/neighb " << (i++) << ": " << randomCell << " " << randomNeighbor << endl;
    root1 = maze.find(randomCell);
    root2 = maze.find(randomNeighbor);
    if(root1 != root2){
    //if(maze.find(randomCell) != maze.find(randomNeighbor)){
      //maze.unionSets(randomCell, randomNeighbor);
      maze.unionSets(root1,root2);
      //knock down the wall between these cells
      maze.clearWall(randomCell,randomNeighbor);
    }
  }

  //randomly knock down a few more walls?
}

/*
void printMaze(DisjSet& maze, int rows, int cols)
{
  int i, j;
  string output;

  //make top border
  output += "\n  _";
  for(i = 0; i < MATRIX_COLS-2; i++)
    output += "__";
  output += "_\n|";

  for(i = 0; i < rows; i++){
    for(j = 0; j < cols; j++){
      //on a right edge (only check down)
      if(j == (cols-1)){
        if(maze.mazeameSets(i,i+cols))
          output += " |\n|";
        else
          output += "_|\n|";
      }
      //on bottom row (only check right)
      else if(i == (rows-1)){
        if(maze.mazeameSets(i,i+1))
          output += "__";
        else
          output += "_|";
      }
      //else check both right and down
      else{
        //check downstairs first
        if(maze.mazeameSets(i,i+cols))
          output += " ";
        else
          output += "_";

        //then check nextdoor
        if(maze.mazeameSets(i,i+1))
          output += "_";
        else
          output += "|";
      }
    }
  }
  //chop the extra pipe
  output[output.size()-1] = '\0';

/*
  //make bottomborder
  output += "\n|";
  for(i = 0; i < MATRIX_COLS-1; i++)
    output += "~~";
  output += "~|\n|";


  cout << output << endl;
}
*/

/*
void printMaze(DisjSet& maze, int rows, int cols)
{
  int i, j;
  string output, line;
  bool checkRight, checkDown;

  //make top border
  output += "\n|";
  for(i = 0; i < MATRIX_COLS-1; i++)
    output += "~~";
  output += "~|\n|";

  for(i = 0; i < rows; i++){
    for(j = 0 ; j < cols; j++){
      //top row, so look only 
      checkRight = (j != cols -1);
      checkDown = (i != rows - 1);

      if(checkRight){
        //check if right-neighbor belongs to same set
        if(maze.findCompress(i*cols + j) == maze.findCompress(i*cols + j + 1)){
          output += "  ";
        }
        else{
          output += " |";
        }
      }
      else{
        output += " |";
      }

      if(checkDown){
        //check if lower-neighbor belongs to same set
        if(maze.findCompress(i*cols + j) == maze.findCompress((i+1)*cols + j)){
          if(checkRight){
            line += " -";
          }
          else{
            line += " |";
          }
        }
        else{
          if(checkRight){
            line += "--";
          }
          else{
            line += "-|";
          }
        }
      }
    }
    output += "\n|";
    if(i != rows - 1){
      output += line;
      output += "\n|";
      line.clear();
    }
  }

  //make top border
  for(i = 0; i < MATRIX_COLS-1; i++)
    output += "~~";void DisjSet::clearWall(int cell1, int cell2)
  output += "~|";

  cout << output << endl;
}
*/

int main(void)
{
  DisjSet amaze(MATRIX_ROWS * MATRIX_COLS);

  srand(time(NULL));

  amaze.printSet();
  amaze.printMaze();
  makeMaze(amaze);
  amaze.printSet();
  amaze.printMaze();

  return 0;
}

