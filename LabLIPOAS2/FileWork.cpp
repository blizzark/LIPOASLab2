#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "Menu.h"
#include "PrimeNumber.h"
#include "Matrix.h"

using namespace std;
using namespace Menu;
using namespace PrimeNumber;
using namespace matrix;
namespace FileWork {
	// Цвета
	enum ConsoleColors {
		LightGray = 7,
		LightGreen = 10,
		LightRed = 12,
	};
	// Пункты меню.
	enum IntMenu {
		Yes = 1,
		No,
	};




	

	// Проверка файла
	bool FileCheck(string fileName) {
		ifstream file;
		file.open(fileName);
		int sizeMatrix, check;
		int counter = 0;
		file >> sizeMatrix;

		const int MaxSize = 50;
		const int MinSizeLines = 2;
		const int NumberMax = 1000000;
		const int NumberMin = 0;

		if ((sizeMatrix <= MaxSize) && (sizeMatrix >= MinSizeLines)) {
			for (int i = 0; i < sizeMatrix*sizeMatrix; i++) {
				if (!file.eof()) {
					if (file >> check) {
						if ((check <= NumberMax) && (check >= NumberMin)) {
							counter += 1;
							if (counter == sizeMatrix * sizeMatrix) {
								return true;
								break;
							}
						}
						else {
							return false;
							break;
						}
					}
				}
			}
		}
		else {
			return 0;
		}
		if (counter < sizeMatrix*sizeMatrix) {
			return false;
		}
		file.close();
		return false;
	}


	void FileInputFun() {
		int sizeMatrix = 0;
		string fileName = "";
		cout << "Введите полный путь к файлу: ";
		getline(cin, fileName);
		ifstream file;
		file.open(fileName);
		if (std::experimental::filesystem::is_regular_file(fileName) && file.good() && (FileCheck(fileName) == true)) {
			ColorChange("Файл открыт!", LightGreen);
			cout << endl;
			if (!file.eof()) {
				file >> sizeMatrix;
				int ***arrFile = new int**[sizeMatrix];


				for (int i = 0; i < sizeMatrix; i++)
				{
					arrFile[i] = new int*[sizeMatrix];
					for (int j = 0; j < sizeMatrix; j++)
					{
						arrFile[i][j] = new int[2];
						arrFile[i][j][1] = 0;
						file >> arrFile[i][j][0];
						arrFile[i][j][1] = CheckingTheNumber(arrFile[i][j][0]);
					}
				}

				Matrix arr = Matrix(arrFile, sizeMatrix);
				
				for (size_t i = 0; i < sizeMatrix; i++)
				{
					for (size_t j = 0; j < sizeMatrix; j++)
						delete[] arrFile[i][j];
					delete[] arrFile[i];
				}
				delete[] arrFile;

				cout << "Введённая матрица:" << endl;
				arr.OutputScreen();

				cout << endl << "Результат: " << endl;

				string output = "";

				arr.HorizontallyChecking(output);
				arr.VerticallyChecking(output);
				arr.DiagonalCheckingDownLeft(output);
				arr.DiagonalCheckingUpRight(output);


				cout << output << endl;

			}
			else {
				ColorChange("Формат файла не поддерживается!", LightRed);
				cout << endl;

			}
		}
		else {
			ColorChange("Ошибка открытия файла!", LightRed);
			cout << endl;
		}

	}
}