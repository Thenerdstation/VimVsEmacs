#include <cassert>
#include <iostream>
#include "location.h"


// CONSTRUCTOR
Location::Location (int r, int c, int rot) : row(r), column(c), rotation(rot) { 
	//std::cout<< rot << std::endl;
	  assert (rotation == 0 || 
          rotation == 90 || 
          rotation == 180 || 
          rotation == 270); 
}

Location::Location (int r, int c) : row(r), column(c), rotation(0) {}

bool Location::operator<(const Location& loc)
{
	if(row < loc.row)
		return true;
	if(row > loc.row)
		return false;
	else
	{
		if(column < loc.column)
			return true;
		else
			return false;
	}
}
Location & Location::operator=( const Location& loc)
{
	row = loc.row;
	column = loc.column;
	rotation = loc.rotation;
}
bool operator==(const Location& loc1, const Location& loc2)
{
	return loc1.row == loc2.row && loc1.column == loc2.column;
}
bool operator!= (const Location& loc1, const Location& loc2)
{
	return loc1.row != loc2.row || loc1.column != loc2.column;
}
bool operator<(const Location &loc1, const Location& loc2)
{
	//it compares the row position first and then the column position
	if(loc1.row < loc2.row)
		return true;
	if(loc2.row < loc1.row)
		return false;
	else
	{
		if(loc1.column< loc2.column)
			return true;
		else
			return false;
	}
}
// helper function to output the placement of this tile within a solution
std::ostream& operator<<(std::ostream &ostr, const Location &loc) {
  ostr << "(" << loc.row << "," << loc.column << "," << loc.rotation << ")";
  return ostr;
}
