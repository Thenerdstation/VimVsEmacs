bool IsTileAlone(Board & board, int x, int y)
{
  //checks if the tile is not next to another tile
  return !(x != 0 && board.getTile(x -1, y) != NULL
  || x != board.numRows() -1 && board.getTile(x +1, y) != NULL
  || y != 0 && board.getTile(x, y-1) != NULL
  || y != board.numColumns() -1 && board.getTile(x, y+ 1) != NULL);
}
bool IsTileLegal(Board & board, const int x, const int y)
{
  //this funciton is long and gross 
  //It just checks if the current tile is placed legally.
  //A lot of the code is very repetative, but due to how the 
  //board and tile classes are structured, there is no simple
  //way of making it into a for loop.

  //checks if the tile is just NULL
  if(board.getTile(x,y) == NULL)
    return true;
    //checks if tile is not touching another tile
  if(IsTileAlone(board, x, y))
    return false;
  //checks above the tile to make sure that the 
  //touching tile has a side that is the correct type
  if(x != 0)
  {
    if(board.getTile(x-1, y) != NULL 
      && board.getTile(x,y)->getNorth() != board.getTile(x-1,y)->getSouth())
        return false;
  }
  else if(x == 0 &&board.getTile(x,y)->getNorth()!= "pasture")
    return false;
  //checks below
  if(x != board.numRows()-1)
  {
    if(board.getTile(x+1, y) != NULL 
      && board.getTile(x,y)->getSouth() != board.getTile(x+1,y)->getNorth())
        return false;
  }
  else if(x == board.numRows() -1 &&board.getTile(x,y)->getSouth()!= "pasture")
    return false;
 // checks to the left
  if(y != 0)
  {
    if(board.getTile(x, y-1) != NULL 
      &&  board.getTile(x,y)->getWest() != board.getTile(x,y-1)->getEast())
        return false;
  }
  else if(y == 0 &&board.getTile(x,y)->getWest()!= "pasture")
    return false;
  //checks to the right
  if(y != board.numColumns() - 1)
  {
    if(board.getTile(x, y + 1) != NULL 
      && board.getTile(x,y)->getEast() == board.getTile(x,y+1)->getWest())
        return false;
  }
  else if(y == board.numColumns() - 1 &&board.getTile(x,y)->getEast()!= "pasture")
    return false;
  return true;
}
bool IsTileSolved(Board board, const int x, const int y)
{
  //this function now checks if the tile placed can be in a 
  //final solved position. Meaning that there are no
  //unclosed roads or cities and there are no cities or
  //roads on the edge of the map.
  if(IsTileLegal(board, x, y))
  {
    if(board.getTile(x,y) != NULL)
    {
      if(board.getTile(x,y)->getNorth() != "pasture")
        if(x == 0 || board.getTile(x-1,y) == NULL)
          return false;
      if( board.getTile(x,y)->getSouth() != "pasture")
        if(x == board.numRows() -1 || board.getTile(x+1,y) == NULL)
          return false;
      if( board.getTile(x,y)->getWest() != "pasture")
        if(y == 0 || board.getTile(x,y-1) == NULL)
          return false;
      if( board.getTile(x,y)->getEast() != "pasture")
        if(y == board.numColumns() -1 || board.getTile(x,y+1) == NULL)
          return false;
    }
    return true;
  }
  return false;
}
bool IsSolution(Board &board)
{
  //this makes sure every single tile on the 
  //board is placed in a solved position.
  bool blank = true;
  for(int x = 0; x < board.numRows(); x++)
  {
    for(int y = 0; y < board.numColumns(); y++)
    {
      if(board.getTile(x,y) != NULL)
        blank = false; 
      if(!IsTileSolved(board, x, y))
        return false; 
    }
  }
  return !blank; // the board isn't solved if it's blank!
}

void PrintSolution(Board& board, std::vector<Location> locations)
{
  //simply prints out solution
  std::cout << "Solution: ";
  for(int x = 0; x < locations.size(); x++)
    std::cout<< locations[x];
  std::cout << std::endl;
  board.Print();
}
bool IsAlreadySolved(std::vector<std::vector<Location> >& solvedLoc, const std::vector<Location> & locations)
{
  std::vector<Location> tempLoc;
  for(int x = 0; x < locations.size(); x++)
  {
    tempLoc.push_back(locations[x]);
  }
  bool found = false;
  sort(tempLoc.begin(), tempLoc.end()); // the sorting helps with              
  found = false;                        //switched tiles double counting
  for(int x = 0; x < solvedLoc.size(); x++)
  {
    found = true;
    for(int y = 0; y < solvedLoc[x].size(); y++)
    {
      if (solvedLoc[x][y] != tempLoc[y]) // checks for an unsimilar position
      {
        found = false;
        break;
      }
    }
    if(found)
      break;
  }
    if(!found)
  { //adds solution to solution vector
    solvedLoc.push_back(tempLoc);
  }
  return found;
}
void RemakeBoard(Board & board, const std::vector<Tile*> & tiles, const std::vector<Location>& locations,
                  std::vector<std::vector<Location> >& solvedLoc, int& numSol)
{
  //The purpose of this board is to take the 
  //the old board and slide it as far up and to the left
  //as possible. It then sees if that solution already exists 
  //and prints it if it isnt.
  int maxHeight, minHeight, maxWidth, minWidth;
  std::vector<Location> loc;
  for(int x = 0; x < locations.size(); x++)
  {
    if(x == 0)
    {
      minHeight = maxHeight =locations[0].row;
      minWidth = maxWidth = locations[0].column;
    }
    if(maxHeight < locations[x].row)
      maxHeight = locations[x].row;
    if(minHeight > locations[x].row)
      minHeight = locations[x].row;
    if(maxWidth < locations[x].column)
      maxWidth = locations[x].column;
    if(minWidth > locations[x].column)
      minWidth = locations[x].column;
  }
  Board brd(maxHeight - minHeight + 1, maxWidth - minWidth + 1);
  for(int x = 0; x < locations.size(); x++)
  {
    brd.setTile(locations[x].row - minHeight, locations[x].column- minWidth, tiles[x]);
    loc.push_back(Location(locations[x].row - minHeight, locations[x].column - minWidth, locations[x].rotation));
  }
  if(!IsAlreadySolved(solvedLoc, loc))
  {
    numSol++;
    PrintSolution(brd, loc);
  }
}
//This is the heart of the algorithm
bool BackTracking(Board & board, std::vector<Tile*> & tiles, std::vector<Location> & locations,
                   std::vector<std::vector<Location> >& solvedLoc, int height, int width, 
                   int numTile, bool all_solutions, bool allow_rotations, int& numSol)
{
  if(height < -1) // avoids seg faults
    height = -1;
  if(width < 0)// avoids seg faults
    width = 0;
  if(numTile == tiles.size()) // if last tile was placed, check for solution
  {
    if(IsSolution(board))
    {
      RemakeBoard(board, tiles, locations, solvedLoc, numSol);
      if(!all_solutions)//if you want all the solutions, it doesn't return true 
        return true;    // so that all of combinations are tried
    }
    return false;
  }
  do 
  {
    height++;
    if(height == board.numRows())
    { //Checks the next column
      height = 0;
      width++;
    }
    if(width == board.numColumns())
    {
      //this applies the rotations
      if(allow_rotations && numTile !=0) // forcing the first tile not to be rotateable prevents 
      {                                  // the program from outputting entired rotated board solutions
        tiles[numTile]->Rotate();
        if(tiles[numTile]->getRotation() == 3)
        {
          return false;
        }
        else
          //it continues the recursion with the newly rotated tile
          return BackTracking(board, tiles, locations, solvedLoc, -1, 0, numTile, all_solutions, allow_rotations, numSol);
      }
      else
        return false;
    }
  } while(board.getTile(height, width) != NULL); // it looks for a not NULL board position
  board.setTile(height, width, tiles[numTile]);
  locations.push_back(Location(height, width, tiles[numTile]->getRotation()*90));
  if(numTile == 0 || IsTileLegal(board, height, width))
  {
    //it tries the next tile and if it fails it places the current tile in the next position
    if(!BackTracking(board, tiles, locations, solvedLoc, -1, 0, numTile +1, all_solutions, allow_rotations, numSol))
    {
      board.setTile(height, width, NULL);
      locations.pop_back();
     return BackTracking(board, tiles, locations, solvedLoc, height, width, numTile, all_solutions, allow_rotations, numSol);
    }
    else
      return true;
  }
  else
  { //if the tile isn't legal, it places it in the next position
    board.setTile(height, width, NULL);
    locations.pop_back();
    return BackTracking(board, tiles, locations, solvedLoc, height, width, numTile, all_solutions, allow_rotations, numSol);
  }
}
