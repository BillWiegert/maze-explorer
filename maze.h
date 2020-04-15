/*
  maze.h: Provides the maze_type class, which reads a maze from a text file
    and wanders through it to find the treasure.
  Uses the

  -RPM 15.03.2016.

  MAZE DESCRIPTION

  For long ages, your people have suffered from the oppressive rule of the
  Iota Surreality. But you have finally stolen their secret weapon, the
  mythic Division By Zero. Your task now is to enter the Maze of Mad Math
  and find the Infinite Well, rid the world of the Division By Zero, and
  escape the maze!

  The maze is made up of a grid of "cells" connected by spaces ("corridors")
  or separated by walls.  The outside edge is all wall, except for a single
  entrance (cell) somewhere along the bottom edge.

  It is represented by a 2D array of char's, using the symbols below.
  (Well, I used a vector of vectors, but it's basically the same thing. :-)

  The current location of the Hero (that's you!) can be described using the
  array indices as coordinates: x for column, y for row.

  The quest is complete when the Hero is at the entrance to the maze after
  finding the Infinite Well.


  MAZE COORDINATE SYSTEM

  The (0,0) point in the maze is the TOP LEFT cell (should be a wall).
  x increases to the right.
  y increases downward.
      So the "up" direction is (0,-1).


  MAZE SYMBOLS
  The symbols used to represent the maze are stored here as constants.
  (See class definition for the list.)


  CONSTRUCTORS:
  (Note: There is NO DEFAULT CONSTRUCTOR.  It makes no sense to initialize
  an empty maze.)

  maze_type(const string &maze_filename)
    PRECONDITIONS:  maze_filename is the name of a textfile containing the maze to
      be explored.
      The file must include a single entrance character along the bottom edge, and
      include a single Infinite Well (!) somewhere inside.
      The maze should not have any loops.
    POSTCONDITIONS: The contents of the maze file have been loaded into the
    new maze object, and the Hero has been placed at the entrance, facing up
    (north).  Flags such as "found the Infinite Well" are set to false.


  ACCESSORS

  void show_maze() const
    POSTCONDITIONS: Displays the current state of the maze on the screen.

  char get_char(int x, int y) const
    PRECONDITIONS: (x,y) is a valid location in the maze.
    POSTCONDITIONS: Returns the char representing the maze at the given position.

  char get_char(const vector2d& pos) const
    PRECONDITIONS: pos is a valid location in the maze.
    POSTCONDITIONS: Returns the char representing the maze at the given position.

  int get_x() const
  int get_y() const
    POSTCONDITIONS: Returns the x or y coordinate of the Hero's current location.

  vector2d get_pos() const
    POSTCONDITIOSN: Returns the Hero's current location as an (x,y) pair.

  vector2d get_facing_dir() const
    POSTCONDITIONS: Returns the direction the Hero is currently facing.

  vector2d get_facing_pos() const
    POSTCONDITION: Return the position the Hero is currently facing.

  bool facing_wall() const
    POSTCONDITIONS: Returns true if the Hero is facing a wall, or false otherwise.

  bool facing_seen() const
    POSTCONDITIONS: Returns true if the Hero is facing a corridor that has already
    been visited, or false otherwise.

  bool facing_empty() const
    POSTCONDITIONS: Returns true if the hero is facing an empty corridor that has never been visited.

  bool found_well() const
    POSTCONDITIONS: Returns true if the Hero has found the Infinite Well, or false
    otherwise.

  bool at_entrance() const
    POSTCONDITIONS: Returns true if the Hero is at the entrance to the maze,
    or false otherwise.


  MODIFIERS

  void face_dir(vector2d dir)
    PRECONDITIONS: dir is a valid direction vector ((0,1) etc)
    POSTCONDITIONS: Rotates the Hero to face the given direction, and updates the Hero's char in the maze.

  void turn_left()
    PRECONDITIONS: None.
    POSTCONDITIONS: Rotates the Hero 90 degrees counter-clockwise, and updates the Hero's char in the maze.
      (Note: calling this 4 times should turn in a complete circle.)

  void turn_right()
    PRECONDITIONS: None.
    POSTCONDITIONS: Rotates the Hero 90 degrees clockwise, and updates the Hero's char in the maze.
      (Note: calling this 4 times should turn in a complete circle.)

  bool move_forward()
    PRECONDITIONS: Not facing out of the maze.
    POSTCONDITIONS: Attempts to move the Hero forward (i.e. in the current direction).  Movement fails if the Hero is facing a wall.  Movement marks the old cell as "seen".  (If the old cell contained the Infinite Well, marks it as "Well Found".)
      If the new cell contains the Infinite Well, sets found to true!
      Returns true if the Hero moves, false if not.


  bool move_backward()
    PRECONDITIONS: Back is not facing out of the maze.
    POSTCONDITIONS: Attempts to move the Hero backward (i.e. opposite the current direction).  Movement fails if the Hero's back is to a wall.  Movement marks the old cell as "seen".  (If the old cell contained the Infinite Well, marks it as "Well Found".)
      If the new cell contains the Infinite Well, sets found to true!
      Returns true if the Hero moves, false if not.


  void explore()
    PRECONDITIONS: None.
    POSTCONDITIONS: Possibly recursive function call!
      After this function is called, one of the following situations is true:
      1. The Hero has FULLY explored the maze in all unvisited directions from the current position, WITHOUT finding the Infinite well, and returned to the place where explore_maze was called from, facing the original direction.  (If the Hero is at a dead end, nothing happens.)  Each spot the Hero explored has been marked as "visited".
      2. The Hero found the Infinite Well (yay!) and returned to the place where explore_maze was called from, facing the original direction.  Each spot the Hero explored has been marked as "visited", EXCEPT that the location of the Infinite Well is marked by a different character.

  HELPER FUNCTIONS

  void explore_assist()
    PRECONDITIONS: Only to be called by the explore function.
    POSTCONDITIONS: Explores the path in the current direction, if possible.
  */

#ifndef __MAZE_H__  // Prevent loading this file twice.
#define __MAZE_H__

#include <vector>
#include <iostream> // for cout

#include "vector2d.h"

using namespace std;

class maze_type {
public:

  /***********************************/
  /***  Characters to display the maze  ***/

  /***  PLEASE USE THESE instead of hard-coding characters. ***/

  static const char ENTRANCE   ='O';
  static const char WALL       ='@';
  static const char UNVISITED  =' ';
  static const char VISITED    ='+';
  static const char GOAL       ='!'; // The Infinite Well!
  static const char GOAL_FOUND ='$'; // The Infinite Well, after it's found.

  static const char HERO_U = '^';
  static const char HERO_D = 'V';
  static const char HERO_L = '<';
  static const char HERO_R = '>';

  // Coordinate directions (so we don't have to keep track of + and -).
  // Values are set in the .cpp file.  (Apparently this is what you have to do
  // for static constants that are objects.)
  static const vector2d UP;
  static const vector2d DOWN;
  static const vector2d LEFT;
  static const vector2d RIGHT;

  /***  Constructor  ***/
  maze_type(const string &maze_filename);

  /***  Accessors  ***/
  void show_maze() const;
  char get_char(int x, int y) const { return maze[x][y]; }
  char get_char(const vector2d& pos) const { return get_char(pos.x(), pos.y()); }
  int get_x() const {return hero_pos.x();}
  int get_y() const {return hero_pos.y();}
  vector2d get_pos() const { return hero_pos; }
  vector2d get_facing_dir() const { return facing; }
  vector2d get_facing_pos() const { return hero_pos + facing; }
  vector2d get_well_pos() const { return goal_pos; }
  bool facing_wall() const;
  bool facing_seen() const;
  bool facing_empty() const {return (!facing_wall()) && (!facing_seen());}
  bool found_well() const {return found;}
  bool at_entrance() const;

  /***  Modifiers  ***/
  void face_dir(const vector2d& dir);
  void turn_left();
  void turn_right();
  bool move_forward();
  bool move_backward();
  void explore();


private:

  /***********************************/
  /***  Private member variables  ***/

  vector< vector<char> > maze; // Access: maze[col][row], i.e. maze[x][y].  maze[0][0] is top left.
  int dimx, dimy; // Number of characters in the x and y direction of the maze.

  vector2d hero_pos; // Hero's current position.
  vector2d facing; // Direction that the Hero is facing.

  bool found; // Has the Hero found the Infinite Well?

  vector2d entrance_pos; // Coordinates of the maze entrance.
  vector2d goal_pos; // The location of the Infinite Well.

  int nmoves; // Number of forward moves made (useful for testing, e.g. show maze on every 10th move).

  /***********************************/
  /***  Private member functions  ***/

  void explore_assist(); // Used by explore function to keep code DRY.
  void set_maze_char(const vector2d& pos, char c); // Sets the char at the given maze coordinate.
  void update_hero_char(); // Updates the character representing the Hero so that it points in the correct direction.

}; // class maze_type

#endif  // defined __MAZE_H__
