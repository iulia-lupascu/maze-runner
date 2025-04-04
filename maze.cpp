#include "Maze.h"
#include <sstream>
#include <cstdlib>

// Converts an integer representing a cell type into a corresponding character
char Maze::getMazeChar(int cell) {
    switch (cell) {
        case 0: return ' '; // Path
        case 1: return '#'; // Wall
        case 2: return 's'; // Start
        case 3: return 'e'; // End
        case 4: return '8'; // Googles
        case 5: return '-'; // Speed potion
        case 6: return '*'; // Fog
        case 7: return '_'; // Slowpoke potion
        default: return ' ';
    }
}

// Extracts the digit from a string and converts it to an integer
int Maze::clean(std::string word) {
    for (char c : word) {
        if (isdigit(c)) {
            return c - '0'; // Convert the character digit to an integer
        }
    }
    return 0; // Return 0 if no digit is found
}

// Initializes the maze from a file.
void Maze::initializeMaze(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "File not found" << std::endl;
        return; // Exit if the file cannot be opened
    }

    std::string line;
    int i = 0;
    bool pass_through = false;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '[' || line[0] == ']') {
            continue; // Skip irrelevant lines
        }

        std::stringstream ss(line);  // Read a line from the file 
        std::vector<char> row;
        std::string word;
        int cell;
        row.push_back('#'); // Start each row with a wall
        i++;
        while (ss >> word) {  // Breaks up the string stream into seperate strings using the space as a delimitor
            cell = clean(word); // Convert word to cell type
            char ch = getMazeChar(cell); // Get the character representation
            if (ch == 's') {
                startingPosition = {i, row.size()}; // Set starting position
            } else if (ch == 'e') {
                endPosition = {i, row.size()}; // Set end position
            }
            row.push_back(ch); // Add the cell to the row
        }
        row.push_back('#'); // End each row with a wall
        if(!pass_through) {
            std::vector<char> wallRow(row.size(), '#'); 
            mazeMatrix.push_back(wallRow); // Add a top row of walls
            pass_through = true; // Set the variable to true so it knows not to pass through the loop again (we only need one top border)
        }

        mazeMatrix.push_back(row); // Add the row to the maze
    }

    std::vector<char> bottomWallRow(mazeMatrix[0].size(), '#');
    mazeMatrix.push_back(bottomWallRow); // Add a bottom row of walls

    std::cout << "Maze initialized with " << mazeMatrix.size() << " rows and " << mazeMatrix[0].size() << " columns" << std::endl;
}

// The constructor initializes the maze using the given file name
Maze::Maze(const std::string &fileName) {
    initializeMaze(fileName);
}

// Displays the maze and the current position of the agent
void Maze::displayAgentandMaze(const std::pair<int, int>& agentPos) {
    for (int i = 0; i < mazeMatrix.size(); i++) {
        for (int j = 0; j < mazeMatrix[i].size(); j++) {
            std::cout << (i == agentPos.first && j == agentPos.second ? '@' : mazeMatrix[i][j]) << " "; // Display the agent ("@") instead of what was displayed int he maze
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Returns the starting position in the maze.
std::pair<int, int> Maze::getStartingPosition() const {
    return startingPosition;
}

// Returns the end position in the maze.
std::pair<int, int> Maze::getEndPosition() const {
    return endPosition;
}

// Returns the character at a given position in the maze.
char Maze::getCharacter(std::pair<int, int> position) const {
    return mazeMatrix[position.first][position.second];
}

// Generates and returns a list of possible moves from a given position.
std::vector<std::pair<int,int>> Maze::getPossibleMoves(const std::pair<int,int>& current_position) {
    std::vector<std::pair<int, int>> possible_moves;
    // Add all adjacent positions (up, right, down, left) as possible moves
    possible_moves.emplace_back(current_position.first - 1, current_position.second);
    possible_moves.emplace_back(current_position.first, current_position.second + 1);
    possible_moves.emplace_back(current_position.first + 1, current_position.second);
    possible_moves.emplace_back(current_position.first, current_position.second - 1);
    return possible_moves;
}