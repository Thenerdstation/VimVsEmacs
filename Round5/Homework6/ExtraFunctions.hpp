void FindMinAndMax(Board & board, int height, int width)
{
  if(height == board.hMax && board.hMax < board.numRows())
    board.hMax = height +1;
  if(height == board.hMin && board.hMin>0)
    board.hMin= height -1;
  if(width == board.wMax && board.wMax < board.numColumns())
    board.wMax = width +1;
  if(width == board.wMin && board.wMin > 0)
    board.wMin = width -1;
}
void CheckMaxAndMin(Board & board, int height, int width)
{
  if(height == board.hMax -1)
  {
    bool found = false;
    for(int x = board.wMin; x < board.wMax; x++)
    {
      if (board.getTile(board.hMax-1, x) != NULL)
        found = true;
    }
    if(!found)
    {
      board.hMax = height;
    }
  }
  if(height == board.hMin + 1)
  {
    bool found = false;
    for(int x = board.wMin; x < board.wMax; x++)
    {
      if (board.getTile(board.hMin +1, x) != NULL)
        found = true;
    }
    if(!found)
    {
      board.hMin++;
    }
  }
   if(width == board.wMax -1)
  {
    bool found = false;
    for(int x = board.hMin ; x < board.hMax; x++)
    {
      if (board.getTile(x, board.wMax -1) != NULL)
        found = true;
    }
    if(!found)
    {
      board.wMax--;
    }
  }
  if(width == board.wMin + 1)
  {
    bool found = false;
    for(int x = board.hMin; x < board.hMax; x++)
    {
      if (board.getTile(x, board.wMin+ 1) != NULL)
        found = true;   
    }
    if(!found)
    {
      board.wMin++;
    }
  }
}
bool DynamicBackTracking(Board & board, std::vector<Tile*> & tiles, std::vector<Location> & locations,
                 int height, int width, int numTile, bool all_solutions, bool allow_rotations)
{
  if(numTile == tiles.size())
  {
    if(IsSolution(board))
    {
      RemakeBoard(board, tiles, locations);
      if(!all_solutions)
        return true;
    }
    return false;
  }
  if(numTile == 0)
  {
    board.setTile(board.numRows()/2, board.numColumns()/2, tiles[numTile]);
    locations.push_back(Location(board.numRows()/2, board.numColumns()/2, 0));
    return DynamicBackTracking(board, tiles, locations, board.hMin- 1, board.wMin,
                    numTile + 1, all_solutions, allow_rotations);
  }
  do
  {
    height++;
    if(height == board.hMax+1)
    {
      height = board.hMin;
      width++;
    }
    if(width == board.wMax+1)
    {
      if(allow_rotations && numTile !=0) // forcing the first tile not to be rotateable prevents 
      {                                  // the program from outputting entired rotated board solutions
        tiles[numTile]->Rotate();
        if(tiles[numTile]->getRotation() == 3)
        {
          return false;
        }
        else
          return DynamicBackTracking(board, tiles, locations, board.hMin-1, board.wMin, numTile, all_solutions, allow_rotations);
      }
      else
        return false;
    }
  } while(board.getTile(height, width) != NULL);
  board.setTile(height, width, tiles[numTile]);
  locations.push_back(Location(height, width, tiles[numTile]->getRotation()*90));
 // board.Print();
  if(numTile == 0 || IsTileLegal(board, height, width))
  {
    FindMinAndMax(board, height, width);
    if(!DynamicBackTracking(board, tiles, locations, board.hMin-1, board.wMin, numTile +1, all_solutions, allow_rotations))
    {
      board.setTile(height, width, NULL);
      locations.pop_back();
      CheckMaxAndMin(board, height, width);
     return DynamicBackTracking(board, tiles, locations, height, width, numTile, all_solutions, allow_rotations);
    }
    else
    {
      return true;
    }
  }
  else
  {
    board.setTile(height, width, NULL);
    locations.pop_back();
    CheckMaxAndMin(board, height, width);
    return DynamicBackTracking(board, tiles, locations, height, width, numTile, all_solutions, allow_rotations);
  }
}