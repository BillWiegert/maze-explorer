// FILE: vector2d.h
// CLASS PROVIDED: vector2d
//
//   Modified from point2d class
//   by Michael Main and Walter Savitch, "Data Structures and Other 
//   Objects Using C++" (4th edition), Addision-Wesley (2011).
//
// This version is IMMUTABLE, meaning once a vector2d object is created
// there are no methods to modify it.  (You can still replace it by assignment.)
// Technically this is weaker than truly "immutable" but it'll do for our 
// purposes.
//
// CONSTRUCTOR for the vector2d class:
//   vector2d(int initial_x = 0, int initial_y = 0)
//     Postcondition: The point has been set to (initial_x, initial_y).
//
// CONSTANT MEMBER FUNCTIONS for the vector2d class:
//   int x( ) const
//     Postcondition: The value returned is the x coordinate of the point.
//
//   int y( ) const
//     Postcondition: The value returned is the y coordinate of the point.
//
//   vector2d add(int x_amount, int y_amount) const
//     Postcondition: Returns a vector that's been moved by x_amount along the x axis
//     and by y_amount along the y axis.
//
//   vector2d add(const vector2d& v) const
//     Postcondition: Returns the sum of this and the given vector.
//
//   vector2d rotate90ccw( ) const
//     Postcondition: Returns the point rotated counterclockwise by 90 degrees.
//
//   vector2d rotate90cw( ) const
//     Postcondition: Returns the point rotated clockwise by 90 degrees.
//
//   vector2d toString() const
//     Postcondition: Returns a (x,y) string representing the vector.
//
// NON-MEMBER FUNCTIONS associated with this class:
//   vector2d operator+(const vector2d& a, const vector2d& b)
//     Postcondition: Returns a vector that's the element-wise sum of a+b.
//
// VALUE SEMANTICS for the vector2d class:
//    Assignments and the copy constructor may be used with vector2d objects.

#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

#include <string>

class vector2d
{
public:
    // CONSTRUCTOR
    vector2d(int initial_x = 0, int initial_y = 0);
    // CONSTANT MEMBER FUNCTIONS
    int x( ) const { return _x; } 
    int y( ) const { return _y; }
    vector2d add (int x_amount, int y_amount) const;
    vector2d add(const vector2d& v) const;
    vector2d rotate90cw( ) const;
    vector2d rotate90ccw( ) const;
    std::string toString() const;
private:
    int _x; // x coordinate of this vector2d
    int _y; // y coordinate of this vector2d
};

// NON-MEMBER FUNCTIONS
vector2d operator+(const vector2d& a, const vector2d& b);
bool operator==(const vector2d& a, const vector2d& b);


#endif // defined __VECTOR2D_H__
