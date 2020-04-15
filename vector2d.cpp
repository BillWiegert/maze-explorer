// FILE: vector2d.cpp
// CLASS IMPLEMENTED: vector2d (See vector2d.h for documentation.)

#include <string>
#include <sstream>
#include "vector2d.h"

vector2d::vector2d(int initial_x, int initial_y) {
  _x = initial_x;   // Constructor sets the point to a given position.
  _y = initial_y;
}


vector2d vector2d::add(int x_amount, int y_amount) const {
  return vector2d(_x+x_amount, _y+y_amount);
}


vector2d vector2d::add(const vector2d& v) const {
  return vector2d(_x+v.x(), _y+v.y());
}


vector2d vector2d::rotate90cw( ) const {
  int new_x;
  int new_y;

  new_y = _x;  // For a 90 degree clockwise rotation, the new _y is the original _x,
  new_x = -_y; // and the new _y is -1 times the original _x.
  
  return vector2d(new_x, new_y);
}


vector2d vector2d::rotate90ccw( ) const {
  int new_x;
  int new_y;

  new_x = _y;  // For a 90 degree counterclockwise rotation, the new _x is the original _y,
  new_y = -_x; // and the new _y is -1 times the original _x.

  return vector2d(new_x, new_y);
}


std::string vector2d::toString() const{
  std::stringstream ss;
  ss << "(" << x() << ", " << y() << ")";
  return ss.str();
}


vector2d operator+(const vector2d& a, const vector2d& b) {
  return a.add(b);
}

bool operator==(const vector2d& a, const vector2d& b) {
  return (a.x()==b.x()) && (a.y()==b.y());
}

