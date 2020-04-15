/*
Bill Wiegert
CMPT276
Lab 5
04-14-2020

  maze.cpp: Implements the maze_type class, which reads a maze from a
  	text file and wanders through it to find the treasure.

  See maze.h for documentation.

  -RPM 15.03.2016

*/

#include<fstream> // for file input
#include<cassert> // for assert
#include<cstdlib> // for exit

#include "maze.h"
#include "vector2d.h"

using namespace std;

/**********************************************************/
/***           CLASS STATIC MEMBER VARIABLES.           ***/
/**********************************************************/

const vector2d maze_type::UP    = vector2d(0, -1);
const vector2d maze_type::DOWN  = vector2d(0,  1);
const vector2d maze_type::LEFT  = vector2d(-1, 0);
const vector2d maze_type::RIGHT = vector2d( 1, 0);

/**********************************************************/
/***               CLASS MEMBER FUNCTIONS.              ***/
/**********************************************************/

/***********************************/
/***  Constructor  ***/

maze_type::maze_type(const string &maze_filename) {
  // Constructor.  Loads the maze from the given filename, and positions
  // the Hero at the entrance.
  // Uses the exit function from cstdlib.

  string line, lastrow;
  ifstream mazefile(maze_filename.c_str());
  if (!mazefile) {
    cout << "Bork!  Could not open file " << maze_filename << endl;
    exit(EXIT_FAILURE); // exit terminates the program (does not return to main!).
  }

  /////
  // Read the maze from the file.

  dimy = 0; // This will count the number of rows we read in.
  while (mazefile) {
    getline(mazefile, line); // Read one line from the file.
    if (line.empty())
      break;

    // If this is the first line, reserve all the columns we need.
    // Remember that maze is a "vector of vectors" (each element is a vector of char's).
    if (maze.empty()) {
      dimx = line.length();
      maze.resize(dimx);
    }

    // Add each character in this row to the bottom of the appropriate column.
    for (int i = 0; i < line.length(); ++i) {
      maze[i].push_back(line[i]);
    }

    ++dimy; // Count the row.
    lastrow = line;
  } // while (mazefile)

  mazefile.close();

  /////
  // Find the entrance and the goal, and place the Hero.
  // The entrance should be in the last row in the maze.

  for (int iy = 0; iy < dimy; ++iy) {
    for (int ix = 0; ix < dimx; ++ix) {
      if (maze[ix][iy] == ENTRANCE) {
        entrance_pos = vector2d(ix, iy);
      }
      if (maze[ix][iy] == GOAL) {
        goal_pos = vector2d(ix, iy);
      }
    }
  }

  hero_pos = entrance_pos;

  // Start facing up (into the maze).
  face_dir(UP);
  update_hero_char();

  found = false; // Have not yet found the Infinite Well.

  nmoves = 0; // No moves made yet.

} // maze_type::maze_type()

/***********************************/
/***  Accessors ***/

void maze_type::show_maze() const {
  // Display the maze on the screen.

  for (int iy = 0; iy < dimy; ++iy) {
    for (int ix = 0; ix < dimx; ++ix)
        cout << maze[ix][iy];
    cout << endl;
  }
  cout << endl; // blank line
} // maze_type::show_maze()

bool maze_type::facing_wall() const {
  return get_char(get_facing_pos()) == maze_type::WALL;
}

bool maze_type::facing_seen() const {
  return get_char(get_facing_pos()) == maze_type::VISITED;
}

bool maze_type::at_entrance() const {
  return hero_pos == entrance_pos;
}

/***********************************/
/***  Modifiers ***/

void maze_type::face_dir(const vector2d& dir) {
  // Face the Hero in the given direction.
  facing = dir;
  update_hero_char();
} // maze_type::face_dir()

void maze_type::turn_left() {
  facing = facing.rotate90ccw();
  update_hero_char();
}

void maze_type::turn_right() {
  facing = facing.rotate90cw();
  update_hero_char();
}

bool maze_type::move_forward() {
  if (facing_wall()) {
    return false; // Can't move forward
  }

  //mark current spot as "SEEN" or "GOAL_FOUND" if it was the goal
  hero_pos == goal_pos ?
  set_maze_char(hero_pos, maze_type::GOAL_FOUND) : set_maze_char(hero_pos, maze_type::VISITED);

  //move to new spot
  hero_pos = get_facing_pos();

  //if new spot is well set found to true
  if (hero_pos == goal_pos) { found = true; }

  update_hero_char();

  return true;
}

bool maze_type::move_backward() {
  // Store facing direction
  vector2d initial_facing = facing;

  // Face backwards
  facing = facing.rotate90cw().rotate90cw();

  // Move forward
  bool moved = move_forward();

  // Restore facing direction
  facing = initial_facing;
  update_hero_char();

  return moved;
}

void maze_type::explore() {
  // Explore left path <
  turn_left();
  explore_assist();

  // Explore forward path ^
  turn_right();
  explore_assist();

  // Explore right path >
  turn_right();
  explore_assist();

  // Resume facing ^
  turn_left();
}


/***********************************/
/***  Private member functions  ***/

// Helper function for explore()
void maze_type::explore_assist() {
  // If hero is facing an open and unexplored path, move forward
  if (facing_empty() and move_forward()) {
    explore(); // Explore from this new position
    move_backward(); // Return back to previous position
  }
}

//////////
void maze_type::set_maze_char(const vector2d& pos, char c) {
  // PRECONDITIONS: pos is a valid maze coordinate; c is a valid maze character.
  // POSTCONDITION: Assigns the character to the given maze position.
  maze[pos.x()][pos.y()] = c;
}

//////////
void maze_type::update_hero_char() {
  // Updates the character representing the Hero so that it points in the correct direction.
  char c = 'X'; // default, should never be used.
  if (facing == UP) {
    c = HERO_U;
  } else if (facing == DOWN) {
    c = HERO_D;
  } else if (facing == LEFT) {
    c = HERO_L;
  } else if (facing == RIGHT) {
    c = HERO_R;
  }
  set_maze_char(hero_pos, c);
}
