#include "Matrix.h"
#include "Menu.h"
#include <string>
#include <iostream>
#include "PrimeNumber.h"
#include <ctime>
#include <tuple>

using std::cout; // ������������ ���� std ��� cout
using std::cin; // ������������ ���� std ��� cin
using std::endl; // ������������ ���� std ��� endl
using std::to_string;
using std::string;
using std::ifstream;
using namespace std;
using Menu::IntegerCheck;
using Menu::ColorChange;
using Menu::YesNo;
using namespace PrimeNumber;
// ������ ���������� �������.
namespace matrix {
	enum InputMethods {
		Snake = 1,
		Snail,
	};
	// ������ ����.
	enum TypeSaving {
		SaveArray = 1,
		SaveResult,
	};
	// �����
	enum ConsoleColors {
		LightGray = 7,
		LightGreen = 10,
		LightRed = 12,
		Yellow = 14,
	};
	// ������ ����.
	enum IntMenu {
		Yes = 1,
		No,
	};
	Matrix::Matrix()
	{
		for (size_t i = 0; i < sizeMatrix; i++)
		{
			arr[i] = new int*[sizeMatrix];
			for (size_t j = 0; j < sizeMatrix; j++)
			{
				arr[i][j] = new int[2];
				arr[i][j][1] = 0;
				arr[i][j][0] = 0;
			}

		}
	}

	Matrix::Matrix(int*** &arrFile, int size) {
		this->sizeMatrix = size;
		arr = new int**[sizeMatrix]();

		for (size_t i = 0; i < sizeMatrix; i++)
		{
			arr[i] = new int*[sizeMatrix];  
			for (size_t j = 0; j < sizeMatrix; j++)
			{
				arr[i][j] = new int[2];
				arr[i][j][1] = arrFile[i][j][1];
				arr[i][j][0] = arrFile[i][j][0];
			}

		}
	}

	Matrix::Matrix(int sizeMatrix)
	{
		this->sizeMatrix = sizeMatrix;
		arr = new int**[sizeMatrix](); // �������� ����� � ������ ��� ���������
	}


	int*** Matrix::GetArray() {
		return arr;
	}

	void Matrix::OutputScreen() {
		cout << " ^" << endl;
		for (size_t i = 0; i < sizeMatrix; i++)
		{
			cout << sizeMatrix - (i + 1) << "|\t";
			for (size_t j = 0; j < sizeMatrix; j++)
			{

				if (arr[i][j][1] == 1) {
					ColorChange(to_string(arr[i][j][0]), LightGreen);
					cout << '\t';
				}
				else
					cout << arr[i][j][0] << '\t';


				if (j == sizeMatrix - 1)
					cout << endl << endl;

			}
		}
		cout << " |" << endl;
		for (size_t i = 0; i < sizeMatrix + 1; i++)
		{
			cout << " �\t";
		}
		cout << ">" << endl;
		for (size_t i = 0; i < sizeMatrix; i++)
		{
			cout << "\t " << i;
		}
	}

	void Matrix::SaveToFile(int choiceTypeSave, const string &output) {
		bool is_file_save_successful = false;
		string path;
		bool first = true;
		do {
			if (first) {
				cout << endl << "���� �� ������ ������ ��� �����, �� �� ����� � ����� � ��������." << endl;
				cout << "��� ���������� ����� � ������ ����� ������� ������ ���� � �����." << endl;
				cout << "(�� ��������� � ����� ����������� .txt)" << endl << endl;
				first = false;
			}
			cout << endl << "������� ���� � �����: ";
			cin >> path;
			path += ".txt";
			bool is_file_exist = false;
			if (ifstream(path)) // ��������� �� ���.
				is_file_exist = true;

			ofstream file;
			file.open(path, ios::app);

			if (file.good()) {
				if (!std::experimental::filesystem::is_regular_file(path)) {
					ColorChange("������������ ��� �����.", LightRed);
					file.close();
					continue;
				}
				if (is_file_exist) {
					cout << "������ ���� ����������! ������������?" << endl;
					if (YesNo() == No) {
						file.close();
						continue;

					}
				}

				file.close();
				file.open(path, ios::trunc);

				file << sizeMatrix << '\n';

				for (size_t i = 0; i < sizeMatrix; i++) {
					for (size_t j = 0; j < sizeMatrix; j++) {
						file << " " << arr[i][j][0];
					}
					file << '\n';
				}

				if (choiceTypeSave == SaveResult) {
					file << output;
				}

				file.close();
				is_file_save_successful = true;
				ColorChange("���� ������� �������!", LightGreen);
				cout << endl;


			}
			else {
				ColorChange("������ ��� �������� �����.", LightRed);
				file.close();
			}
		} while (!is_file_save_successful);
	}


	void Matrix::ManualInputFun(int choiceFilling) {


		const int min = 1;
		const int max = 100000;

		if (choiceFilling == Snake) {
			for (size_t i = 0; i < sizeMatrix; i++)
			{
				arr[i] = new int*[sizeMatrix]; // �� ������� ����� � ����� ������� ������ ���� ������� � ������������? 
				if (i % 2 == 0) {
					for (size_t j = 0; j < sizeMatrix; j++)
					{
						arr[i][j] = new int[2]; // ������ ��� ����� �� �����. ��������.
						arr[i][j][1] = 0;
						arr[i][j][0] = IntegerCheck(min, max);
						arr[i][j][1] = PrimeNumber::CheckingTheNumber(arr[i][j][0]);
					}
				}
				else {
					for (int j = static_cast<int>(sizeMatrix) - 1; j >= 0; j--)
					{
						arr[i][j] = new int[2];
						arr[i][j][1] = 0;
						arr[i][j][0] = IntegerCheck(min, max);
						arr[i][j][1] = PrimeNumber::CheckingTheNumber(arr[i][j][0]);
					}
				}
			}
		}
		if (choiceFilling == Snail) {

			for (size_t i = 0; i < sizeMatrix; i++)
				arr[i] = new int*[sizeMatrix];


			for (size_t i = 0; i < sizeMatrix; i++)
				for (size_t j = 0; j < sizeMatrix; j++)
				{
					arr[i][j] = new int[2];
					arr[i][j][1] = 0;
					arr[i][j][0] = 0;
				}

			int count = 0;

			for (int y = 0; y < sizeMatrix; y++) {
				count++;
				arr[0][y][0] = IntegerCheck(min, max);
				arr[0][y][1] = PrimeNumber::CheckingTheNumber(arr[0][y][0]);
			}
			for (int x = 1; x < sizeMatrix; x++) {
				count++;
				arr[x][sizeMatrix - 1][0] = IntegerCheck(min, max);
				arr[x][sizeMatrix - 1][1] = PrimeNumber::CheckingTheNumber(arr[x][sizeMatrix - 1][0]);
			}
			for (int y = static_cast<int>(sizeMatrix) - 2; y >= 0; y--) {
				count++;
				arr[static_cast<int>(sizeMatrix) - 1][y][0] = IntegerCheck(min, max);
				arr[static_cast<int>(sizeMatrix) - 1][y][1] = PrimeNumber::CheckingTheNumber(arr[static_cast<int>(sizeMatrix) - 1][y][0]);

			}
			for (int x = static_cast<int>(sizeMatrix) - 2; x > 0; x--) {
				count++;
				arr[x][0][0] = IntegerCheck(min, max);
				arr[x][0][1] = PrimeNumber::CheckingTheNumber(arr[x][0][0]);
			}

			int c = 1;
			int d = 1;


			for (size_t i = count; i < sizeMatrix * sizeMatrix; i++)
			{

				//�������� ������.
				while (arr[c][d + 1][0] == 0) {
					arr[c][d][0] = IntegerCheck(min, max);
					arr[c][d][1] = PrimeNumber::CheckingTheNumber(arr[c][d][0]);
					d++;
				}

				//�������� ����.
				while (arr[c + 1][d][0] == 0) {
					arr[c][d][0] = IntegerCheck(min, max);
					arr[c][d][1] = PrimeNumber::CheckingTheNumber(arr[c][d][0]);
					c++;
				}

				//�������� �����.
				while (arr[c][d - 1][0] == 0) {
					arr[c][d][0] = IntegerCheck(min, max);
					arr[c][d][1] = PrimeNumber::CheckingTheNumber(arr[c][d][0]);
					d--;
				}

				//�������� �����.
				while (arr[c - 1][d][0] == 0) {
					arr[c][d][0] = IntegerCheck(min, max);
					arr[c][d][1] = PrimeNumber::CheckingTheNumber(arr[c][d][0]);
					c--;
				}
			}

			//��� ������ ������� � ������ ������ ������� ������������� ������.
			//������� � ��� ������ ���������� �����.
			for (int x = 0; x < sizeMatrix; x++) {
				for (int y = 0; y < sizeMatrix; y++) {
					if (arr[x][y][0] == 0) {
						arr[x][y][0] = IntegerCheck(min, max);
						arr[x][y][1] = PrimeNumber::CheckingTheNumber(arr[x][y][0]);
					}
				}
			}

		}
	}


	void Matrix::RandomInputFun() {
		srand((unsigned)time(0));
		for (size_t i = 0; i < sizeMatrix; i++)
		{
			arr[i] = new int*[sizeMatrix];
			for (size_t j = 0; j < sizeMatrix; j++)
			{
				arr[i][j] = new int[2];
				arr[i][j][1] = 0;
				arr[i][j][0] = rand() % 100000;

				arr[i][j][1] = PrimeNumber::CheckingTheNumber(arr[i][j][0]);

			}
		}
	}

	void Matrix::AutoInputFun(int startNum, int choiceFilling) {


		if (choiceFilling == Snake) {
			for (size_t i = 0; i < sizeMatrix; i++)
			{
				arr[i] = new int*[sizeMatrix];
				if (i % 2 == 0) {
					for (size_t j = 0; j < sizeMatrix; j++)
					{
						arr[i][j] = new int[2];
						arr[i][j][1] = 0;
						arr[i][j][0] = startNum++;
						arr[i][j][1] = PrimeNumber::CheckingTheNumber(arr[i][j][0]);
					}
				}
				else {
					for (int j = static_cast<int>(sizeMatrix) - 1; j >= 0; j--)
					{
						arr[i][j] = new int[2];
						arr[i][j][1] = 0;
						arr[i][j][0] = startNum++;
						arr[i][j][1] = PrimeNumber::CheckingTheNumber(arr[i][j][0]);
					}
				}
			}
		}
		if (choiceFilling == Snail) {

			for (size_t i = 0; i < sizeMatrix; i++)
				arr[i] = new int*[sizeMatrix];


			for (size_t i = 0; i < sizeMatrix; i++)
				for (size_t j = 0; j < sizeMatrix; j++)
				{
					arr[i][j] = new int[2];
					arr[i][j][1] = 0;
					arr[i][j][0] = 0;
				}

			int count = 0;

			for (int y = 0; y < sizeMatrix; y++) {
				count++;
				arr[0][y][0] = startNum++;
				arr[0][y][1] = PrimeNumber::CheckingTheNumber(arr[0][y][0]);
			}
			for (int x = 1; x < sizeMatrix; x++) {
				count++;
				arr[x][sizeMatrix - 1][0] = startNum++;
				arr[x][sizeMatrix - 1][1] = PrimeNumber::CheckingTheNumber(arr[x][sizeMatrix - 1][0]);
			}
			for (int y = static_cast<int>(sizeMatrix) - 2; y >= 0; y--) {
				count++;
				arr[static_cast<int>(sizeMatrix) - 1][y][0] = startNum++;
				arr[static_cast<int>(sizeMatrix) - 1][y][1] = PrimeNumber::CheckingTheNumber(arr[static_cast<int>(sizeMatrix) - 1][y][0]);

			}
			for (int x = static_cast<int>(sizeMatrix) - 2; x > 0; x--) {
				count++;
				arr[x][0][0] = startNum++;
				arr[x][0][1] = PrimeNumber::CheckingTheNumber(arr[x][0][0]);
			}

			int c = 1;
			int d = 1;


			for (size_t i = count; i < sizeMatrix * sizeMatrix; i++)
			{

				//�������� ������.
				while (arr[c][d + 1][0] == 0) {
					arr[c][d][0] = startNum++;
					arr[c][d][1] = PrimeNumber::CheckingTheNumber(arr[c][d][0]);
					d++;
				}

				//�������� ����.
				while (arr[c + 1][d][0] == 0) {
					arr[c][d][0] = startNum++;
					arr[c][d][1] = PrimeNumber::CheckingTheNumber(arr[c][d][0]);
					c++;
				}

				//�������� �����.
				while (arr[c][d - 1][0] == 0) {
					arr[c][d][0] = startNum++;
					arr[c][d][1] = PrimeNumber::CheckingTheNumber(arr[c][d][0]);
					d--;
				}

				//�������� �����.
				while (arr[c - 1][d][0] == 0) {
					arr[c][d][0] = startNum++;
					arr[c][d][1] = PrimeNumber::CheckingTheNumber(arr[c][d][0]);
					c--;
				}
			}

			//��� ������ ������� � ������ ������ ������� ������������� ������.
			//������� � ��� ������ ���������� �����.
			for (int x = 0; x < sizeMatrix; x++) {
				for (int y = 0; y < sizeMatrix; y++) {
					if (arr[x][y][0] == 0) {
						arr[x][y][0] = startNum;
						arr[x][y][1] = PrimeNumber::CheckingTheNumber(arr[x][y][0]);
					}
				}
			}

		}


	}
	void Matrix::HorizontallyChecking(string &output) {
		bool quantity = false;
		output += "�������������(�):\n";
		output += "y = a, (y = const)\n";

		for (size_t i = 0; i < sizeMatrix; i++)
		{
			int count = 0;
			size_t j = 0;
			for (; j < sizeMatrix; j++)
			{
				if (arr[i][j][1] == 1)
					count++;

			}
			if (static_cast<int>((double)count / (double)sizeMatrix*100.0) > percent) {
				quantity = true;
				output += "��� �: " + to_string(sizeMatrix - i - 1);
				output += " = ";
				output += to_string(static_cast<int>((double)count / (double)sizeMatrix*100.0));
				output += "% (" + to_string(count);
				output += "��)\n";
			}

		}
		if (!quantity) {
			output += "��� �������� ������ ";
			output += to_string(percent);
			output += "%\n";
		}
	}

	void Matrix::VerticallyChecking(string &output) {
		bool quantity = false;
		output += "�����������(|):\n";
		output += "x = b, � = const\n";

		for (size_t i = 0; i < sizeMatrix; i++)
		{
			int count = 0;
			size_t j = 0;
			for (; j < sizeMatrix; j++)
			{
				if (arr[j][i][1] == 1)
					count++;

			}
			if (static_cast<int>((double)count / (double)sizeMatrix*100.0) > percent) {
				quantity = true;
				output += "��� b: " + to_string(i);
				output += " = ";
				output += to_string(static_cast<int>((double)count / (double)sizeMatrix*100.0));
				output += "% (" + to_string(count);
				output += "��)\n";
			}

		}
		if (!quantity) {
			output += "��� �������� ������ ";
			output += to_string(percent);
			output += "%\n";
		}
	}



	void Matrix::DiagonalCheckingDownLeft(string &output) {
		bool quantity = false;
		output += "�����������(/):\n";
		output += "y = � + b\n";

		int countPrintX = 0;
		int b = sizeMatrix - 1;
		for (int i = 0; i < static_cast<int>(sizeMatrix); i++)  // ����������� ������, ����� ������ �������������� �����������.
		{
			countPrintX++;
			size_t k = 0;
			int count = 0;
			for (int j = i; j >= 0; j--)
			{

				for (; k <= i;)
				{
					if (arr[k][j][1] == 1)
						count++;
					k++; // � �� ���� ������, �� ���� ������� k ����, ������ "warning C4702: ������������ ���" �� ���������
					break;
				}


			}

			if (static_cast<int>((double)count / (double)sizeMatrix*100.0) > percent) {
				quantity = true;
				output += "��� b = ";
				output += to_string(b);
				output += ": ";
				output += to_string(static_cast<int>((double)count / (double)sizeMatrix*100.0));
				output += "% (" + to_string(count);
				output += "��)\n";
			}
			b--;

		}
		size_t l = 1;
		for (size_t i = sizeMatrix - 1; i > 0; i--)
		{
			countPrintX++;
			size_t k = l;

			int count = 0;
			for (size_t j = sizeMatrix - 1; j >= l; j--)
			{
				for (; k <= sizeMatrix - 1;)
				{
					if (arr[k][j][1] == 1)
						count++;
					k++; // � �� ���� ������, �� ���� ������� k ����, ������ "warning C4702: ������������ ���" �� ���������
					break;
				}
			}
			l++;
			if (static_cast<int>((double)count / (double)sizeMatrix*100.0) > percent) {
				quantity = true;
				output += "��� b = ";
				output += to_string(b);
				output += ": ";
				output += to_string(static_cast<int>((double)count / (double)sizeMatrix*100.0));
				output += "% (" + to_string(count);
				output += "��)\n";
			}
			b--;

		}
		if (!quantity) {
			output += "��� �������� ������ ";
			output += to_string(percent);
			output += "%\n";
		}
	}



	void Matrix::DiagonalCheckingUpRight(string &output) {
		bool quantity = false;
		output += "�����������(\\):\n";
		output += "y = -1 * � + b\n";
		int b = sizeMatrix + sizeMatrix - 2;
		int countPrintX = 0;

		for (int i = static_cast<int>(sizeMatrix) - 1; i >= 0; i--)
		{
			int count = 0;
			size_t k = 0;
			countPrintX++;
			for (int j = i; j < static_cast<int>(sizeMatrix); j++)
			{

				for (; k < sizeMatrix - i;)
				{
					if (arr[k][j][1] == 1)
						count++;
					k++; // � �� ���� ������, �� ���� ������� k ����, ������ "warning C4702: ������������ ���" �� ���������
					break;

				}

			}
			if (static_cast<int>((double)count / (double)sizeMatrix*100.0) > percent) {
				quantity = true;
				output += "��� b = ";
				output += to_string(b);
				output += ": ";
				output += to_string(static_cast<int>((double)count / (double)sizeMatrix*100.0));
				output += "% (" + to_string(count);
				output += "��)\n";
			}
			b--;
		}

		size_t l = 1;
		for (size_t i = 0; i < sizeMatrix - 1; i++) {

			int count = 0;
			size_t k = l;
			countPrintX++;
			for (size_t j = 0; j < sizeMatrix - i; j++) {
				for (; k < sizeMatrix;)
				{
					if (arr[k][j][1] == 1)
						count++;
					k++; // � �� ���� ������, �� ���� ������� k ����, ������ "warning C4702: ������������ ���" �� ���������
					break;

				}

			}
			l++;
			if (static_cast<int>((double)count / (double)sizeMatrix*100.0) > percent) {
				quantity = true;
				output += "��� b = ";
				output += to_string(b);
				output += ": ";
				output += to_string(static_cast<int>((double)count / (double)sizeMatrix*100.0));
				output += "% (" + to_string(count);
				output += "��)\n";
			}
			b--;
		}
		if (!quantity) {
			output += "��� �������� ������ ";
			output += to_string(percent);
			output += "%\n";
		}


	}

	Matrix::~Matrix()
	{
		for (size_t i = 0; i < sizeMatrix; i++)
		{
			for (size_t j = 0; j < sizeMatrix; j++)
				delete[] arr[i][j];
			delete[] arr[i];
		}
		delete[] arr;
	}
}