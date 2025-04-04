#include "Agent.h"
#include <algorithm>
#include <cstdlib>

// The constructor initializes the agent with the given maze and sets the current position to the maze's starting position
Agent::Agent(Maze& maze) : mazeMatrix(maze), current_position(maze.getStartingPosition()) {
    path_stack.push(current_position); // Push the starting position onto the path stack
    visited_positions.push_back(current_position); // Mark the starting position as visited
}

// Checks if the given position is the goal (end position of the maze)
bool Agent::isGoal(std::pair<int, int> position) const {
    return position == mazeMatrix.getEndPosition();
}

// Checks if a potential move is valid: not a wall and not already visited
bool Agent::isValid(std::pair<int, int> possible_move) const {
    return mazeMatrix.getCharacter(possible_move) != '#' &&
           std::find(visited_positions.begin(), visited_positions.end(), possible_move) == visited_positions.end();
}

// Checks if a position has already been visited
bool Agent::isVisited(std::pair<int, int> position) const {
    return std::find(visited_positions.begin(), visited_positions.end(), position) != visited_positions.end();
}

// Marks a position as visited by adding it to the visited_positions vector
void Agent::markVisited(const std::pair<int,int>& position) {
    visited_positions.push_back(position);
}

// Returns the current position of the agent
std::pair<int, int> Agent::getCurrentPosition() const {
    return current_position;
}

// Moves the agent one step in the maze (the Depth-First Search Algorithm)
std::pair<int, int> Agent::moveOneStep() {
    if (!isGoal(current_position)) { // Check if the current position is not the goal
        // Get all possible moves from the current position
        std::vector<std::pair<int, int>> possible_moves = mazeMatrix.getPossibleMoves(current_position);
        std::vector<std::pair<int, int>> legal_moves; // Vector to store valid moves

        // Check each possible move for validity and add to legal_moves if valid
        for (const auto& move : possible_moves) {
            if (isValid(move) && !isVisited(move)) {
                legal_moves.push_back(move);
            }
        }

        // If there are legal moves available, choose one at random and move there
        if (!legal_moves.empty()) {
            isBacktracking = false; // Set backtracking checker to false
            int randomMove = rand() % legal_moves.size(); // Choose a random legal move
            current_position = legal_moves[randomMove]; // Update current position
            path_stack.push(current_position); // Push the new position onto the path stack
            markVisited(current_position); // Mark the new position as visited
        } else {
            // If no legal moves are available, start backtracking
            if (!path_stack.empty()) {
                 if (isBacktracking == false)
                {
                    isBacktracking = true; // Set backtracking checker to true
                    return current_position;
                }  
                path_stack.pop(); // Pop the last position from the stack to backtrack
                if (!path_stack.empty()) {
                    current_position = path_stack.top(); // Update current position to the new top of the stack
                }
            }
            // Check if the stack is empty and if so, return to the starting position
            else {
                current_position = mazeMatrix.getStartingPosition();
                return current_position;
            }
        }
        
    }
    return current_position; // Return the current (possibly new) position
}
