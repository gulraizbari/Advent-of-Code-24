#include <iostream>
#include <fstream>
#include <regex>

int ReadFileAndCalculateSum(const std::string &fileName)
{
    std::ifstream InputFile(fileName);
    if (!InputFile)
    {
        std::cerr << "Error: Could not open file: " << fileName << std::endl;
        return -1;
    }

    std::string line;
    std::regex pattern("mul\\((\\d+),(\\d+)\\)"); // captures x and y in mul(x,y)
    std::vector<std::pair<int, int>> matches;
    int totalSum = 0;

    while (std::getline(InputFile, line))
    {
        auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto end = std::sregex_iterator();
        for (auto index = begin; index != end; ++index)
        {
            std::smatch match = *index; // dereferencing to access value of the object
            int x = std::stoi(match[1].str());
            int y = std::stoi(match[2].str());
            matches.emplace_back(x, y);
        };
    };

    for (const auto &pair : matches)
    {
        totalSum += pair.first * pair.second;
    };

    return totalSum;
};

int main(int argc, char *argv[])
{
    std::string fileName = "./input.txt";
    int sum = ReadFileAndCalculateSum(fileName);
    std::cout << "Total Sum: " << sum << std::endl;

    return 0;
};