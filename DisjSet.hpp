#ifndef DISJ_SET_H
#define DISJ_SET_H

// DisjSets class
//
// CONSTRUCTION: with int representing initial number of sets
//
// ******************PUBLIC OPERATIONS*********************
// void union( root1, root2 ) --> Merge two sets
// int find( x )              --> Return set containing x
// ******************ERRORS********************************
// No error checking is performed

#include <vector>
#include <iostream>
#include "MazeCell.hpp"

#define MATRIX_ROWS 25
#define ROWS MATRIX_ROWS
#define MATRIX_COLS 50
#define COLS MATRIX_COLS
#define LEFT 0
#define DOWN 1
#define RIGHT 2
#define UP 3



using std::vector;
using std::cout;
using std::endl;
using std::string;



/**
 * Disjoint set class.
 * Use union by rank and path compression.
 * Elements in the set are numbered starting at 0.
 */
class DisjSet
{
  public:
    explicit DisjSet( int numElements );
    ~DisjSet();

    void clearWall(int cell1, int cell2);
    void printSet();
    void printMaze();
    bool sameSets(int i, int j);
    int find( int x ) const;
    int findCompress( int x );
    void unionSets( int root1, int root2 );
    vector<MazeCell> maze;
};

#endif

