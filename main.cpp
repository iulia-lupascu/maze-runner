// libraries 
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <windows.h>  
#include "maze.h"
#include "agent.h"

using namespace std;

// in order to run the program i write this comand in the terminal:   g++ -o main maze.cpp agent.cpp main.cpp, and afterwards ./main

int main() {

    bool reached_end = true;

    // Load the maze from a file
    string mazeFile = "C:\\Users\\iulia\\Documents\\uni\\year 3\\C++\\projects\\lectures\\maze\\maze_file.txt"; // file path

    // Create a maze
    Maze maze(mazeFile);

    // Add the seed for random number generation
    srand(time(NULL)); 

    // Create an agent
    Agent agent(maze);
    int step_count = 0;

    while (agent.getCurrentPosition() != maze.getEndPosition()) {

        // Displays the angent's position at every step
        maze.displayAgentandMaze(agent.getCurrentPosition());

        // Move the agent one step
        agent.moveOneStep();

        // Break if the player reaches the end
        if (agent.getCurrentPosition() == maze.getStartingPosition()) {
            reached_end = false;
            break;
        }

        // Count the steps of the agent after each step (including the turning of the agent)
        step_count += 1;

        Sleep(150); // Sleep for 300 milliseconds 

        // Clear the screen
        system("CLS");
    }
    
    if(reached_end == true)
    {
       // Display the agent's final position
       maze.displayAgentandMaze(agent.getCurrentPosition());

       // Display the number of steps it took to complete the maze
       cout<<"The agent took "<<step_count<<" moves to find the exit of the maze";
    }
    else{
        // Display the agent's final position
       maze.displayAgentandMaze(maze.getStartingPosition());

       // Display message
       cout<<"The agent couldn't find teh exit and returned to the starting position";
    }
    
    return 0;
}
     
   