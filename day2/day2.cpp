#include <iostream>
#include <fstream>
#include <sstream>

bool IsReportSafe(const std::vector<int> &levels)
{
    bool isAscending = false;
    bool isDesceding = false;

    for (size_t index = 1; index < levels.size(); ++index)
    {
        int difference = levels[index] - levels[index - 1];
        if (std::abs(difference) < 1 || std::abs(difference) > 3)
        {
            return false;
        }
        if (difference > 0)
        {
            isAscending = true;
        }
        if (difference < 0)
        {
            isDesceding = true;
        }
    }

    return !isAscending || !isDesceding;
};

int ReadFileAndCheckSafeReports(const std::string &fileName)
{
    std::ifstream InputFile(fileName);
    if (!InputFile)
    {
        std::cerr << "Error: Could not open file: " << fileName << std::endl;
        return -1;
    }

    std::string line;
    int safeReportCount = 0;
    while (std::getline(InputFile, line))
    {
        std::istringstream iss(line);
        std::vector<int> levels;
        int level;
        while (iss >> level)
        {
            levels.push_back(level);
        }
        if (IsReportSafe(levels))
        {
            ++safeReportCount;
        };
    };

    InputFile.close();
    return safeReportCount;
};

int main(int argc, char *argv[])
{
    std::string fileName = "./input.txt";
    int safeReportsCount = ReadFileAndCheckSafeReports(fileName);
    std::cout << "Safe Report Count: " << safeReportsCount << std::endl;

    return 0;
};