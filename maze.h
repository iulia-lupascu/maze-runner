// #endif

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// Maze class definition
class Maze {
private:
    std::vector<std::vector<char>> mazeMatrix; // 2D vector representing the maze layout
    std::pair<int, int> startingPosition; // Coordinates of the starting position in the maze
    std::pair<int, int> endPosition; // Coordinates of the end/goal position in the maze

    // Converts a numerical cell value to its character representation in the maze
    char getMazeChar(int cell);

    // Extracts the first digit from a string and converts it to an integer
    int clean(std::string word);

    // Initializes the maze from the contents of a file
    void initializeMaze(const std::string &fileName);

public:
    // The constructor initializes a Maze object by reading maze data from a file
    Maze(const std::string &fileName);

    // Displays the maze and the agent's current position
    void displayAgentandMaze(const std::pair<int, int>& agentPos);

    // Returns the starting position in the maze
    std::pair<int, int> getStartingPosition() const;

    // Returns the end/goal position in the maze
    std::pair<int, int> getEndPosition() const;

    // Returns the character representing the cell at a given position in the maze
    char getCharacter(std::pair<int, int> position) const;

    // Generates and returns a list of possible moves from a given position in the maze
    std::vector<std::pair<int, int>> getPossibleMoves(const std::pair<int, int>& current_position);
};

#endif // MAZE_H
