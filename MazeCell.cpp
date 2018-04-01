#include "MazeCell.hpp"

MazeCell::MazeCell()
{
  i = 0; 
  right = true;
  down = true;
}

MazeCell::MazeCell(const MazeCell& mc)
{
  i = mc.i;
  right = mc.right;
  down = mc.down;
}

MazeCell::MazeCell(int j)
{
  i = j;
  right = true;
  down = true;
};

MazeCell::~MazeCell()
{}
