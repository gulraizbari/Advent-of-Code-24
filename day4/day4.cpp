#include <iostream>
#include <fstream>

std::vector<std::string> ReadFile(const std::string &fileName)
{
    std::ifstream InputFile(fileName);
    if (!InputFile)
    {
        std::cerr << "Error: Could not open file: " << fileName << std::endl;
        return std::vector<std::string>();
    };

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(InputFile, line))
    {
        lines.push_back(line);
    };
    return lines;
};

std::vector<std::pair<int, int>> GenerateDirections()
{
    std::vector<std::pair<int, int>> directions;
    for (int x = -1; x < 2; ++x)
    {
        for (int y = -1; y < 2; ++y)
        {
            if (x != 0 || y != 0)
            {
                // std::cout << "(" << x << "," << y << ")" << std::endl;
                directions.emplace_back(x, y);
            }
        }
    }
    return directions;
};

bool InBound(int rows, int cols, int x, int y)
{
    return x >= 0 && x < rows && y >= 0 && y < cols;
};

// checks whether the word can be found starting at (x, y) in the given direction:
bool IsWordFound(const std::vector<std::string> &grid, int x, int y, const std::vector<std::pair<int, int>> directions, int direction, const std::string &word)
{
    int rows = grid.size();
    int cols = grid[0].size();
    int wordLength = word.size();

    for (int index = 0; index < wordLength; ++index)
    {
        int nx = x + index * directions[direction].first;
        int ny = y + index * directions[direction].second;
        // std::cout << "(" << nx << "," << ny << ")" << std::endl;
        if (!InBound(rows, cols, nx, ny) || grid[nx][ny] != word[index])
        // if current character in the grid does not match the current character in the word return false
        {
            return false;
        }
    };
    return true;
};

int CountOccurences(const std::vector<std::string> &grid, const std::vector<std::pair<int, int>> directions, const std::string &word)
{
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;

    for (int x = 0; x < rows; ++x)
    {
        for (int y = 0; y < cols; ++y)
        {
            for (int directionIndex = 0; directionIndex < directions.size(); ++directionIndex)
            {
                if (IsWordFound(grid, x, y, directions, directionIndex, word))
                {
                    ++count;
                }
            }
        }
    }

    return count;
};

int main(int argc, char *argv[])
{
    std::string fileName = "./input.txt";
    std::string word = "XMAS";

    std::vector<std::string> grid = ReadFile(fileName);
    std::cout << "Number of Lines: " << grid.size() << std::endl;

    std::vector<std::pair<int, int>> directions = GenerateDirections();
    std::cout << "Number of Directions: " << directions.size() << std::endl;

    int wordCount = CountOccurences(grid, directions, word);
    std::cout << "XMAS Word Count: " << wordCount << std::endl;

    return 0;
};