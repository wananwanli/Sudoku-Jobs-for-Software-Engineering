# include <iostream>	
#include <string>
#include <cstdlib> 
#include<random>
#include"game.h"
using namespace std;

int generateRandomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(rng);
}
bool isValidNumber(const std::string& str, int& number) {
	try {
		number = std::stoi(str);
		return true;
	}
	catch (...) {
		return false;
	}
}
bool isValidRange(const std::string& str, int& minRange, int& maxRange) {
	size_t pos = str.find('~');
	if (pos == std::string::npos) {
		return false;
	}

	std::string strMin = str.substr(0, pos);
	std::string strMax = str.substr(pos + 1);

	if (!isValidNumber(strMin, minRange) || !isValidNumber(strMax, maxRange)) {
		return false;
	}

	return true;
}
int main(int argc, char* argv[])
{
	Shudu test;
	if (argc == 3 && std::string(argv[1]) == "-c" ){
		int number = 0;
		if (!isValidNumber(argv[2], number) || number <= 0 || number > 1000000) {
			cout << "������������ʱ���ֲ������ִ��� " << endl;
		}
		else {
			test.generate_terminal(number);
		}
    }
	else if (argc == 3 && std::string(argv[1]) == "-s"){
		test.readandsolve(std::string(argv[2]));
	}
	else if (argc == 5 && std::string(argv[1]) == "-n"&& std::string(argv[3]) == "-m") {
		int number= 0, difficulty =0;
		if (!isValidNumber(argv[2], number) || number <= 0 || number > 10000){
			cout << "����������Ϸʱ����������������" << endl;
		}
		else if (!isValidNumber(argv[4], difficulty) || difficulty <= 0 || difficulty > 3) {
			cout << "����������Ϸʱ�����ѶȲ�������" << endl;
		}
		else {
			if (difficulty == 1) {
				test.generate_game(number, 20);
			}
			else if (difficulty == 2) {
				test.generate_game(number, 35);
			}
			else{
				test.generate_game(number, 55);
			}
			
		}
	}
	else if (argc == 5 && std::string(argv[1]) == "-n" && std::string(argv[3]) == "-r" ) {
		int number = 0;
		int minRange = 0;
		int maxRange = 0;
		if (!isValidNumber(argv[2], number) || number <= 0 || number > 10000) {
			cout << "����ָ���ڿ�����������Ϸʱ����������������" << endl;
		}
		else if (!isValidRange(argv[4], minRange, maxRange) || minRange < 20 || maxRange > 55){
			cout << "�������󣺷�Χ��Ч�򳬳��޶���Χ��" << endl;
		}
		else {
			int randomNumber = generateRandomNumber(minRange, maxRange);
			test.generate_game(number, randomNumber);
		}
	}
	else if (argc == 4 && std::string(argv[1]) == "-n" && std::string(argv[3]) == "-u"){
		int number = 0;
		if (!isValidNumber(argv[2], number) || number <= 0 || number > 10000) {
			cout << "����Ψһ��������Ϸʱ����������������" << endl;
		}else{
			test.generateUniqueSudoku(number);
		}
	}
	else {
		cout << "�����������";
	}
}