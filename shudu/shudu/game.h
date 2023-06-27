#pragma once
#include <vector>
#include <string>

class Shudu
{
public:
    bool isValid(std::vector<std::vector<int>>& board, int row, int col, int num);
    bool solveSudoku(std::vector<std::vector<int>>& board);
    void generateUniqueSudoku(int number);
    bool isonlyone(std::vector<std::vector<int>>& board, int& solutionCount);
    void generateSudoku(int numToRemove);
    void print(const std::vector<std::vector<int>>& board);
    void readandsolve(const std::string& filename);
    void generate_terminal(int num);
    void generate_game(int num, int blank);

private:
    const int BOARD_SIZE = 9;
    const int SUBGRID_SIZE = 3;
    const int EMPTY_CELL = 0;

};
