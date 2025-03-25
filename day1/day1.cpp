#include <iostream>
#include <fstream>
#include <sstream>

void ReadAndAssignFile(const std::string &fileName, std::vector<int> &left, std::vector<int> &right)
{
    std::ifstream InputFile(fileName);

    if (!InputFile)
    {
        std::cerr << "Error: Could not open file: " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(InputFile, line))
    {
        std::istringstream iss(line);
        int leftNum, rightNum;
        if (iss >> leftNum >> rightNum)
        {
            left.push_back(leftNum);
            right.push_back(rightNum);
        }
    }

    InputFile.close();
}

int CalculateDistance(const std::vector<int> &left, const std::vector<int> &right)
{
    std::vector<int> sortedLeft = left;
    std::vector<int> sortedRight = right;

    std::sort(sortedLeft.begin(), sortedLeft.end());
    std::sort(sortedRight.begin(), sortedRight.end());

    int totalDistance = 0;
    for (size_t index = 0; index < sortedLeft.size(); ++index)
    {
        totalDistance += std::abs(sortedLeft[index] - sortedRight[index]);
    };

    return totalDistance;
};

int main(int argc, char *argv[])
{
    std::string fileName = "./input.txt";
    std::vector<int> left;
    std::vector<int> right;
    ReadAndAssignFile(fileName, left, right);

    std::cout << "Left Vector: ";
    for (int num : left)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Right Vector: ";
    for (int num : right)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    int totalDistance = CalculateDistance(left, right);
    std::cout << "Total Distance: " << totalDistance << std::endl;

    return 0;
};