#include "game.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

std::random_device rd;
std::mt19937 rng(rd());

bool Shudu::isValid(std::vector<std::vector<int>>& board, int row, int col, int num)
{
    // 检查行和列
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // 检查子网格
    int startRow = (row / SUBGRID_SIZE) * SUBGRID_SIZE;
    int startCol = (col / SUBGRID_SIZE) * SUBGRID_SIZE;

    for (int i = 0; i < SUBGRID_SIZE; i++) {
        for (int j = 0; j < SUBGRID_SIZE; j++) {
            if (board[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool Shudu::solveSudoku(std::vector<std::vector<int>>& board)
{
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == EMPTY_CELL) {
                std::vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
                std::shuffle(nums.begin(), nums.end(), rng);

                for (int num : nums) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;

                        if (solveSudoku(board)) {
                            return true;
                        }

                        board[row][col] = EMPTY_CELL;
                    }
                }

                return false;
            }
        }
    }
    return true;
}

void Shudu::generateSudoku(int numToRemove)
{
    std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, EMPTY_CELL));
    // 生成数独终盘
    solveSudoku(board);

    // 移除部分数字，生成游戏盘面
    std::uniform_int_distribution<int> dist(0, BOARD_SIZE - 1);

    for (int i = 0; i < numToRemove; i++) {
        int row = dist(rng);
        int col = dist(rng);

        while (board[row][col] == EMPTY_CELL) {
            row = dist(rng);
            col = dist(rng);
        }

        board[row][col] = EMPTY_CELL;
    }
    print(board);
}

void Shudu::print(const std::vector<std::vector<int>>& board)
{
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Shudu::readandsolve(const std::string& filename)
{
    std::ifstream inputFile(filename);
    std::ofstream outputFile("sudoku.txt");

    std::string line;
    std::vector<std::vector<int>> board;
    std::string currentProblemNumber;

    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            if (line.find_first_not_of("0123456789") == std::string::npos) {
                // 当前行为题号
                currentProblemNumber = line;
            }
            else {
                // 解析每行数据并将其存储到数独游戏数据结构中
                std::vector<int> rowValues;
                std::istringstream iss(line);
                int num;

                while (iss >> num) {
                    rowValues.push_back(num);
                }

                board.push_back(rowValues);
            }
        }
        else {
            if (!board.empty()) {
                // 当前数独游戏的读取结束，解决数独并输出结果到文件
                if (solveSudoku(board)) {
                    // 输出题号
                    outputFile << currentProblemNumber << std::endl;

                    // 输出解决后的数独游戏
                    for (const auto& row : board) {
                        for (int num : row) {
                            outputFile << num << " ";
                        }
                        outputFile << std::endl;
                    }
                }
                else {
                    // 输出题号
                    outputFile << currentProblemNumber << std::endl;
                    outputFile << "此题无解！" << std::endl;
                }
                outputFile << std::endl;

                // 清空数独游戏数据结构，准备读取下一个数独游戏
                board.clear();
                currentProblemNumber.clear();
            }
        }
    }

    // 处理最后一个数独游戏（如果有）
    if (!board.empty()) {
        if (solveSudoku(board)) {
            // 输出题号
            outputFile << currentProblemNumber << std::endl;

            // 输出解决后的数独游戏
            for (const auto& row : board) {
                for (int num : row) {
                    outputFile << num << " ";
                }
                outputFile << std::endl;
            }
        }
        else {
            // 输出题号
            outputFile << currentProblemNumber << std::endl;
            outputFile << "此题无解！" << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();
}

void Shudu::generate_terminal(int num)
{
    for (int i = 0; i < num; i++)
    {
        std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, EMPTY_CELL));
        solveSudoku(board);
        print(board);
    }
}

void Shudu::generate_game(int num, int blank)
{
    for (int i = 0; i < num; i++)
    {
        generateSudoku(blank);
    }
}

bool Shudu::isonlyone(std::vector<std::vector<int>>& board, int& solutionCount)
{
    // 寻找空格位置
    int row = -1, col = -1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY_CELL) {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1 && col != -1) {
            break;
        }
    }

    // 所有空格都已填满，找到一个解
    if (row == -1 && col == -1) {
        solutionCount++;
        return true;
    }

    // 尝试填充数字
    for (int num = 1; num <= BOARD_SIZE; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;

            // 继续递归填充下一个空格
            if (isonlyone(board, solutionCount)) {
                // 找到多个解，需要回溯
                if (solutionCount > 1) {
                    return false;
                }
            }

            // 回溯
            board[row][col] = EMPTY_CELL;
        }
    }
    return true;
}

void Shudu::generateUniqueSudoku(int number) {
    for (int i = 0; i < number; i++)
    {
        std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, EMPTY_CELL));
        // 生成数独终盘
        if (!solveSudoku(board)) {
            return;  // 如果无解，则无法生成只有唯一解的数独游戏
        }

        // 备份终盘
        std::vector<std::vector<int>> backupBoard = board;

        // 移除部分数字，生成游戏盘面
        std::uniform_int_distribution<int> dist(0, BOARD_SIZE - 1);

        int numToRemove = (BOARD_SIZE * BOARD_SIZE) / 2;
        int count = 0;

        while (count < numToRemove) {
            int row = dist(rng);
            int col = dist(rng);

            if (board[row][col] != EMPTY_CELL) {
                int temp = board[row][col];
                board[row][col] = EMPTY_CELL;

                // 检查是否仍有唯一解
                std::vector<std::vector<int>> tempBoard = board;
                int solutionCount = 0;
                if (isonlyone(tempBoard, solutionCount) && solutionCount == 1) {
                    count++;
                }
                else {
                    board[row][col] = temp;  // 还原数字
                }
            }
        }
        print(board);
    }
}


