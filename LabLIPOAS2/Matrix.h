#pragma once
#include <string>
#include <fstream>
#include <filesystem>
using namespace std;
namespace matrix {
	class Matrix
	{
	private:
		int ***arr; // ������
		int sizeMatrix; // ������ �������
		const int percent = 10;
	public:
		Matrix();
		Matrix(int***&, int);
		Matrix(int);
		~Matrix();

		int*** GetArray();

		void OutputScreen(); // ����� �������
		void SaveToFile(int, const string &output);
		//����������
		void ManualInputFun(int choiceFilling);
		void RandomInputFun();
		void AutoInputFun(int startNum, int choiceFilling);

		//������� ������� ����� �� ������
		void HorizontallyChecking(std::string &output);
		void VerticallyChecking(std::string &output);
		void DiagonalCheckingDownLeft(std::string &output);
		void DiagonalCheckingUpRight(std::string &output);
	};
}

