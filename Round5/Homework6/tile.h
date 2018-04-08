#ifndef  __TILE_H__
#define __TILE_H__

#include <iostream>
#include <string>
#include <vector>


// This class represents a single Carcassonne tile and includes code
// to produce a human-readable ASCII art representation of the tile.

class Tile {
public:

  // Constructor takes in 4 strings, representing what is on the edge
  // of each tile.  Each edge string is "pasture", "road", or "city".
  Tile(const std::string &north, const std::string &east, const std::string &south, const std::string &west);

  // ACCESSORS
  const std::string& getNorth() const { return side[(0 + rotation) % 4]; }
  const std::string& getSouth() const { return side[(2 + rotation) % 4]; }
  const std::string& getEast() const { return side[(3+ rotation) % 4]; }
  const std::string& getWest() const { return side[(1 + rotation) % 4]; }
  int numCities() const { return num_cities; }
  int numRoads() const { return num_roads; }
  int hasAbbey() const { return (num_cities == 0 && num_roads <= 1); }
  void Rotate() { rotation++;}
  int getRotation() {return rotation % 4;}
  // for ASCII art printing
  void printRow(std::ostream &ostr, int i)const;
  void prepare_ascii_art();

private:

  // REPRESENTATIONs
  std::string north_;
  std::string east_;
  std::string south_;
  std::string west_;
  int num_roads;
  int num_cities;
  int rotation;
  std::vector<std::string> side;
  std::vector<std::string> ascii_art;
};


#endif