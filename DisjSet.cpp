#include "DisjSet.hpp"

/*
  Modified so cells are init'ed to index of cell. Data structure no longer stores height data. -jesse
*/

/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint setmaze.
 */
DisjSet::DisjSet( int numElements )
{
  maze.resize(numElements);

  for(int i = 0; i < maze.size(); i++){
    maze[i].i = i;
    maze[i].right = true;
    maze[i].down = true;
  }
}

DisjSet::~DisjSet()
{
  maze.clear();
}

//knock down the wall between two neighboring cells
void DisjSet::clearWall(int cell1, int cell2)
{
  //map indices into something sensible for the boolean maze representation
  if(cell1 == cell2 - 1)
    maze[cell1].right = false;
  else if(cell2 == cell1 - 1)
    maze[cell2].right = false;
  else if(cell1 == cell2 - COLS)
    maze[cell1].down = false;
  else if(cell2 == cell1 - COLS)
    maze[cell2].down = false;
  else
    cout << "ERROR could not find walls for cells: " << cell1 << ":" << cell2 << endl;
}

/**
 * Union two disjoint setmaze.
 * For simplicity, we assume root1 and root2 are distinct
 * and represent set namemaze.
 * root1 is the root of set 1.
 * root2 is the root of set 2.
 */
void DisjSet::unionSets( int root1, int root2 )
{

  if(root1 > maze.size()){
    cout << "ERROR root1 > size: " << root1 << endl;
  }
  maze[root1].i = root2;

/*
  if( maze[root2] < maze[root1] ){  // root2 is deeper
    maze[root1] = root2;        // Make root2 new root
  }
  else
  {
    //if( maze[root1] == maze[root2] )
    //    maze[root1]--;          // Update height if same
    maze[root2] = root1;        // Make root1 new root
  }
*/
}

void DisjSet::printMaze()
{
  int i, j;

  cout << "  ";
  for(i = 0; i < COLS*2-2; i++)
    cout << "_";
  cout << endl;

  for(i = 0; i < ROWS; i++){
    cout << "|";
    for(j = 0; j < COLS; j++){\
      if((i == ROWS - 1) && (j == COLS - 1)) //very last cell, so leave it open as an "exit" (goal node)
        cout << " ";
      else if(maze[i*COLS + j].down)
        cout << "_";
      else
        cout << " ";

      //print 
      if(maze[i*COLS + j].right)
        cout << "|";
      else
        if((i < ROWS - 1) || (j == (COLS-1) && i == (ROWS-1)))
          cout << " ";
        else
          cout << "_";
    }
    cout << endl;
  }
}


/**
 * Perform a find.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSet::find( int x ) const
{
  if(x >= maze.size() || x < 0){
    cout << "ERROR x invalid in find(): " << x << endl;
    return 0;
  }

  if( maze[x].i == x )
    return x;
  else
    return find( maze[x].i );
}

bool DisjSet::sameSets(int i, int j)
{
  return this->find(i) == this->find(j);
  //return maze[i] == maze[j];
}

void DisjSet::printSet()
{
  for(int i = 0; i < maze.size(); i++){
    std::cout << maze[i].i << " ";
    if(i % 10 == 9)
      cout << endl;
  }
  std::cout << endl;
}

/**
 * Perform a find with path compression.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSet::findCompress(int x)
{
  if(x >= maze.size()){
    cout << "ERROR x too large in findCompress(): " << x << endl;
    return 0;
  }

  if(maze[x].i == x)
    return x;
  else{
    //cout << "ret x=" << x << endl;
    return maze[x].i = findCompress( maze[x].i );
  }
}


