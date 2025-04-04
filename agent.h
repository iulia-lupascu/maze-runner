#ifndef AGENT_H
#define AGENT_H

#include <utility>
#include <vector>
#include <stack>
#include "Maze.h"
// Agent class declaration
class Agent {
private:
    std::pair<int, int> current_position; // Current position of the agent in the maze
    std::stack<std::pair<int, int>> path_stack; // Stack to keep track of the path taken by the agent
    std::vector<std::pair<int, int>> visited_positions; // Vector to keep track of visited positions
    Maze mazeMatrix; // Instance of Maze class to interact with the maze
    bool isBacktracking; // Flag to indicate if the agent is currently backtracking

public:
    // The constructor initializes the agent with a reference to a Maze object
    Agent(Maze& maze);

    // Checks if the given position is the goal/end position of the maze
    bool isGoal(std::pair<int, int> position) const;

    // Checks if a given move is valid (not a wall and not already visited)
    bool isValid(std::pair<int, int> possible_move) const;

    // Checks if a given position has already been visited
    bool isVisited(std::pair<int, int> position) const;

    // Marks a position as visited by adding it to the visited_positions vector
    void markVisited(const std::pair<int,int>& position);

    // Returns the current position of the agent in the maze
    std::pair<int, int> getCurrentPosition() const;

    // Moves the agent one step in the maze, chooses next position or backtracks if necessary
    std::pair<int, int> moveOneStep();
};

#endif // AGENT_H

