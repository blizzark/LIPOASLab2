#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include "FileWork.h"
#include "Matrix.h"

using namespace std;
using namespace matrix;
namespace Menu {
	// ������ ����.
	enum TypesSaving {
		SaveArray = 1,
		SaveResult,
	};

	enum InternalMenuMenu {
		Start = 1,
		Exit = 2,
	};

	enum Menu {
		ManualInput = 1,
		AutoInput,
		RandomInput,
		FileInput,
	};

	// �����
	enum ConsoleColor {
		LightGray = 7,
		LightGreen = 10,
	};
	// ������ ���������� �������.
	enum InputMethod {
		Snake = 1,
		Snail,
	};

	// ������ ����.
	enum InternalMenu {
		Yes = 1,
		No,
		Again,
	};
	bool MainProgram(bool check);
	// �����������
	void Greeting() {
		cout << "������������ ������ �2" << endl;
		cout << "������� ������ � 475: ���������� �����" << endl << endl;
		cout << "  �������� ���������, ������� ���������� ����� ����� �� ���������" << endl;
		cout << "��������� ���������� ������� � �������� �� ������� �����, ��� " << endl;
		cout << "��������� ������� �����. �������� �������, ����������� ������ " << endl;
		cout << "����� �� ����� �������, � ����������� �� �� ���, ������� ��������" << endl;
		cout << "��������� �������� �������; ��������� ����� ���� ������� ����� �� " << endl;
		cout << "���� ������. ���������� ������� ������������� ����� ��������" << endl;
		cout << "�������� ����� ����� �� ��������, ��� ����� ��� ������� ������� ��� " << endl;
		cout << "������� ������ ���������� �������� ������������ ���� (�. 88)." << endl << endl;
	}

	// �������� �� ���������������. ��������� ����������� � ������������ ��������.
	int IntegerCheck(const int& min, const int& max) {
		int tmp = 0;
		cin >> tmp;
		while (cin.fail()) {
			cout << "�������� ����. ������� ������ �����. ��������� ����:";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> tmp;
		}

		if ((tmp >= min) && (tmp <= max)) {
			cin.ignore(INT_MAX, '\n');
			return tmp;
		}
		else {
			cin.ignore(INT_MAX, '\n');
			cout << "�������� ����. ������� ����� � �������� ���������. ��������� ����:";
			tmp = IntegerCheck(min, max);
		}
		return tmp;
	}
	int YesNo() {
		cout << "1. ��." << endl;
		cout << "2. ���." << endl;
		cout << "��� �����: ";

		return IntegerCheck(Yes, No);
	}

	// �������� ����� �� ���������
	int AskSave() {
		cout << endl;
		cout << "������ ��������� � ����?" << endl;
		return YesNo();

	}

	// ��������� �����
	void ColorChange(string text, int color) {
		HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsoleHandle, (WORD)color);
		cout << text;
		SetConsoleTextAttribute(hConsoleHandle, LightGray);
	}


	void ChoiceOfFilling(int inputMethod, int choiceFilling = 0) {
		string buf;
		int sizeMatrix = 0;

		if (inputMethod == ManualInput) {
			cout << "������� ������ ���������� ������� (�� 2 �� 5): ";
			sizeMatrix = IntegerCheck(2, 5);
		}
		else {
			cout << "������� ������ ���������� ������� (�� 2 �� 50): ";
			sizeMatrix = IntegerCheck(2, 50);
		}

		
		Matrix arr = Matrix(sizeMatrix);

		if (inputMethod == ManualInput) {
			cout << "������� ������� (������ ������ � ����� ������ �� 1 �� 90000): " << endl;
			arr.ManualInputFun(choiceFilling);
			cout << "�� �����: " << endl;
			arr.OutputScreen();

		}

		if (inputMethod == AutoInput) {
			cout << "������� ��������� ������ (�� 1 �� 90000): " << endl;
			int startNum = IntegerCheck(1, 90000);
			arr.AutoInputFun(startNum, choiceFilling);
			cout << "�� �����: " << endl;
			arr.OutputScreen();


		}

		if (inputMethod == RandomInput) {
			arr.RandomInputFun();
			cout << "������ ������ �������� ����������� �����" << endl;
			cout << "�� �����: " << endl;
			arr.OutputScreen();


		}
		string output = "";
		if (AskSave() == Yes) {
			arr.SaveToFile(SaveArray, output);
		}

		cout << endl << "���������: " << endl;



		arr.HorizontallyChecking(output);
		arr.VerticallyChecking(output);
		arr.DiagonalCheckingDownLeft(output);
		arr.DiagonalCheckingUpRight(output);

		cout << output << endl;

		if (AskSave() == Yes) {
			arr.SaveToFile(SaveResult, output);
		}
	}



	// ���������������� ����� ������� ��������� �������
	void User�hoice(int inputMethod) {


		cout << "�������� ������ ���������� �������:" << endl;
		cout << "1. ������." << endl;
		cout << "2. ������." << endl;
		cout << endl << "��� �����: ";

		int const NumberItemsMin = 1;
		int const NumberItemsMax = 2;
		switch (IntegerCheck(NumberItemsMin, NumberItemsMax)) {
		case(Snake):
			ChoiceOfFilling(inputMethod, Snake);
			break;
		case(Snail):
			ChoiceOfFilling(inputMethod, Snail);
			break;
		}

	}

	// ������� ����
	bool MainMenu(bool �hoice) {
		if (�hoice) {
			cout << "1. ������ ������." << endl;
		}

		else {
			cout << endl << "����������� ��� ���?" << endl;
			cout << "1. ������ ������" << endl;
		}

		cout << "2. �����." << endl << endl;
		cout << "��� �����: ";
		int const NumberItemsMin = 1;
		int const NumberItemsMax = 2;

		switch (IntegerCheck(NumberItemsMin, NumberItemsMax)) {
		case(Start):
			cout << endl;
			MainProgram(true);
			break;
		case(Exit):
			return false;
		}
		return false;
	}

	bool MainProgram(bool check) {

		if (check == true) {
			cout << "1. ������ ����." << endl;
			cout << "2. �������������� ����������." << endl;
			cout << "3. ��������� ����������." << endl;
			cout << "4. ���� �� �����." << endl;

			cout << endl << "��� �����: ";

			int const NumberItemsMin = 1;
			int const NumberItemsMax = 4;
			switch (IntegerCheck(NumberItemsMin, NumberItemsMax)) {
			case(ManualInput):
				User�hoice(ManualInput);
				break;
			case(AutoInput):
				User�hoice(AutoInput);
				break;
			case(RandomInput):
				ChoiceOfFilling(RandomInput);
				break;
			case(FileInput):
				FileWork::FileInputFun();
				break;
			}

			MainMenu(false);
		}
		return false;
	}
}


