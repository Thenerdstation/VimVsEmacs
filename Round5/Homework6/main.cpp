#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <cassert>
#include <ctime>
#include <list>
#include <cmath>
#include <algorithm>
#include "tile.h"
#include "location.h"
#include "board.h"
//I really didn't want to make this file any larger, 
//so all of the functions I made are in this file.
#include "BackTracking.hpp"

// this global variable is set in main.cpp and is adjustable from the command line
// (you are not allowed to make your own global variables)
int GLOBAL_TILE_SIZE = 11;

// ==========================================================================
// Helper function that is called when an error in the command line
// arguments is detected.
void usage(int argc, char *argv[]) {
  std::cerr << "USAGE: " << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -board_dimensions <h> <w>" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -board_dimensions <h> <w>  -all_solutions" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -board_dimensions <h> <w>  -allow_rotations" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -all_solutions  -allow_rotations" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -tile_size <odd # >= 11>" << std::endl;
  exit(1);
}



// ==========================================================================
// To get you started, this function places tiles on the board and
// randomly and outputs the results (in all likelihood *not* a
// solution!) in the required format


// ==========================================================================
void HandleCommandLineArguments(int argc, char *argv[], std::string &filename, 
                                int &rows, int &columns, bool &all_solutions, bool &allow_rotations) {

  // must at least put the filename on the command line
  if (argc < 2) {
    usage(argc,argv);
  }
  filename = argv[1];

  // parse the optional arguments
  for (int i = 2; i < argc; i++) {
    if (argv[i] == std::string("-tile_size")) {
      i++;
      assert (i < argc);
      GLOBAL_TILE_SIZE = atoi(argv[i]);
      if (GLOBAL_TILE_SIZE < 11 || GLOBAL_TILE_SIZE % 2 == 0) {
        std::cerr << "ERROR: bad tile_size" << std::endl;
        usage(argc,argv);
      }
    } else if (argv[i] == std::string("-all_solutions")) {
      all_solutions = true;
    } else if (argv[i] == std::string("-board_dimensions")) {
      i++;
      assert (i < argc);
      rows = atoi(argv[i]);
      i++;
      assert (i < argc);
      columns = atoi(argv[i]);
      if (rows < 1 || columns < 1) {
        usage(argc,argv);
      }
    } else if (argv[i] == std::string("-allow_rotations")) {
      allow_rotations = true;
    } else {
      std::cerr << "ERROR: unknown argument '" << argv[i] << "'" << std::endl;
      usage(argc,argv);
    }
  }
}


// ==========================================================================
void ParseInputFile(int argc, char *argv[], const std::string &filename, std::vector<Tile*> &tiles) {

  // open the file
  std::ifstream istr(filename.c_str());
  if (!istr) {
    std::cerr << "ERROR: cannot open file '" << filename << "'" << std::endl;
    usage(argc,argv);
  }
  assert (istr);

  // read each line of the file
  std::string token, north, east, south, west;
  while (istr >> token >> north >> east >> south >> west) {
    assert (token == "tile");
    Tile *t = new Tile(north,east,south,west);
    tiles.push_back(t);
  }
}


// ==========================================================================
int main(int argc, char *argv[]) {

  std::string filename;
  int rows = -1;
  int columns = -1;
  bool all_solutions = false;
  bool allow_rotations = false;
  HandleCommandLineArguments(argc, argv, filename, rows, columns, all_solutions, allow_rotations);


  // load in the tiles
  std::vector<Tile*> tiles;
  ParseInputFile(argc,argv,filename,tiles);
  int numSolutions = 0;
  
  if(rows > 1) //runs it when board size is known
  {
    std::vector<Location> loc;
    std::vector<std::vector<Location> > solvedLocations;
    Board board(rows, columns);
    BackTracking(board, tiles, loc, solvedLocations, -1, 0, 0, all_solutions, allow_rotations, numSolutions);
  }
  else
  {
    std::vector<std::vector<Location> > solvedLocations;
    std::vector<Location> loc;
    bool found = false; 
    int solLocNum = 0;//this variable stores the number of solutions found on the previous board size
    //this runs when there is no known board size
    for(int x = sqrt(tiles.size()); x < tiles.size(); x++)
    {
      if(x < 2)
        x = 2;
      Board dynamicBoard(x,x);
      if(BackTracking(dynamicBoard, tiles, loc, solvedLocations, -1, 0, 0, all_solutions, allow_rotations,  numSolutions))
      {
        //this only returns true when all_solutions is false
        break;
      }
      if(solvedLocations.size() == solLocNum && solLocNum !=0)
      {
        break; //breaks when no no solutions are added for the given dimensions
      }
      solLocNum = solvedLocations.size(); // used to compare previous board size to current board size
    }
  }
  if(numSolutions == 0)
    std::cout<< "No Solutions.";
  else if(all_solutions)
  {
    std::cout << "Found " << numSolutions << " Solution(s)."<< std::endl;
  }

  // delete the tiles
  for (int t = 0; t < tiles.size(); t++) 
  {
    delete tiles[t];
  }
}
// ==========================================================================
