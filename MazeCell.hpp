//every cell need only store a right and down flag to indicate walls for the entire matrix/maze
class MazeCell{
  public:
    MazeCell();
    MazeCell(const MazeCell& mc);
    MazeCell(int j);
    ~MazeCell();
    int i;
    bool right;
    bool down;
};
