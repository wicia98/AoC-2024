#include <iostream>
#include <fstream>
#include <vector>

// Function to check if "xmas" exists in a certain direction
bool checkWord(const std::vector<std::vector<char>>& grid, int x, int y, int dx, int dy) {
    std::string word = "XMAS";
    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < word.size(); i++) {
        int newX = x + i * dx;
        int newY = y + i * dy;

        // Out of bounds or mismatch
        if (newX < 0 || newX >= rows || newY < 0 || newY >= cols || grid[newX][newY] != word[i]) {
            return false;
        }
    }
    return true;
}

// Function to count occurrences of "xmas" in all directions
int findXmas(const std::vector<std::vector<char>>& grid) {
    int rows = grid.size();
    if (rows == 0) return 0;  //No rows, return 0 to avoid crash
    int cols = grid[0].size();

    int xmasFound = 0;

    //Define 8 directions: right, left, down, up, diagonals
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},   //Horizontal & Vertical
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}  //Diagonal
    };

    //Loop through every character in the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            //If current letter is 'X', check in all directions
            if (grid[i][j] == 'X') {
                for (auto [dx, dy] : directions) {
                    if (checkWord(grid, i, j, dx, dy)) {
                        xmasFound++;
                    }
                }
            }
        }
    }
    return xmasFound;
}

int main() {
    std::ifstream input("input.txt");
    if (!input) {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
        return 1;   //No file, no fun
    }

    //Read all lines into a vector
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }
    input.close();  //Close file after reading

    if (lines.empty()) {
        std::cerr << "Plik jest pusty!" << std::endl;
        return 1;  //Exit if the file is empty
    }

    int lineAmount = lines.size();
    int lineLength = lines[0].size();  //Assuming all lines are same length

    //Verify all lines have the same length
    for (const auto& l : lines) {
        if (l.size() != lineLength) {
            std::cerr << "Not all lines have same length!" << std::endl;
            return 1;
        }
    }

    //Initialize the 2D grid (letterArray)
    std::vector<std::vector<char>> letterArray(lineAmount, std::vector<char>(lineLength));

    //Fill the 2D vector with characters from the lines
    for (int i = 0; i < lineAmount; i++) {
        for (int j = 0; j < lineLength; j++) {
            letterArray[i][j] = lines[i][j];
        }
    }

    std::cout << "Number of times 'xmas' was found: " << findXmas(letterArray) << std::endl;

    return 0;
}
