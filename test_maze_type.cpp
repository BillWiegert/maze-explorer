/*
  Program for testing maze_type.  -RPM 15.03.16.
*/

#include "maze.h"

using namespace std;

int main(int argc, char *argv[]) {

  string mazefilename;
  if (argc > 1) { // Filename was specified on the command line.
    mazefilename = argv[1]; // argv[0] is the program name.
  } else { // No command line arguments.
    mazefilename = "maze_r4_c4.txt"; // default.
  }

  // cout << "Reading maze from file " << mazefilename << endl;
  maze_type maze(mazefilename);
  maze.show_maze();
  // cout << endl << endl;

  // cout << "Turning in place." << endl;
  // cout << "Left:" << endl;
  // for (int i = 0; i < 4; ++i) { // Loop for testing the turn.
  //   maze.turn_left();
  //   maze.show_maze();
  // }
  // cout << "Right:" << endl;
  // for (int i = 0; i < 4; ++i) { // Loop for testing the turn.
  //   maze.turn_right();
  //   maze.show_maze();
  // }
  // cout << endl << endl;
  //
  //
  // cout << "In and out!" << endl;
  // maze.move_forward();
  // maze.move_backward();
  // maze.show_maze();


  // cout << "Exploring the maze!" << endl << endl;
  maze.explore();

  cout << "Finished exploring!" << endl;
  maze.show_maze();

  if (maze.found_well())
    cout << "Found the Infinite Well at " << maze.get_well_pos().toString() <<
      "!  The world is saved from the Division By Zero!" << endl;
  else
    cout << "Goal not found.  I guess that... didn't go _well_!  B-)" << endl;

} // main()
