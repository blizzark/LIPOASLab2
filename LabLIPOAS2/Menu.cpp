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
	// Пункты меню.
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

	// Цвета
	enum ConsoleColor {
		LightGray = 7,
		LightGreen = 10,
	};
	// Способ заполнения матрицы.
	enum InputMethod {
		Snake = 1,
		Snail,
	};

	// Пункты меню.
	enum InternalMenu {
		Yes = 1,
		No,
		Again,
	};
	bool MainProgram(bool check);
	// Приветствие
	void Greeting() {
		cout << "Лабораторная работа №2" << endl;
		cout << "Студент группы № 475: Овчинников Роман" << endl << endl;
		cout << "  Напишите программу, которая отображает целые числа на плоскость" << endl;
		cout << "некоторым регулярным образом и отмечает на рисунке места, где " << endl;
		cout << "находятся простые числа. Выведите формулы, описывающие прямые " << endl;
		cout << "линии на вашем рисунке, и напечатайте те из них, которые особенно" << endl;
		cout << "изобилуют простыми числами; печатайте также долю простых чисел на " << endl;
		cout << "этих прямых. Обеспечьте высокую эффективность ваших программ" << endl;
		cout << "проверки целых чисел на простоту, так чтобы вам хватило времени для " << endl;
		cout << "анализа весьма отдаленных отрезков натурального ряда (с. 88)." << endl << endl;
	}

	// Проверка на целочисленность. Принимает минимальное и максимальное значение.
	int IntegerCheck(const int& min, const int& max) {
		int tmp = 0;
		cin >> tmp;
		while (cin.fail()) {
			cout << "Неверный ввод. Вводите только цифры. Повторите ввод:";
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
			cout << "Неверный ввод. Вводите цифры в пределах диапазона. Повторите ввод:";
			tmp = IntegerCheck(min, max);
		}
		return tmp;
	}
	int YesNo() {
		cout << "1. Да." << endl;
		cout << "2. Нет." << endl;
		cout << "Ваш выбор: ";

		return IntegerCheck(Yes, No);
	}

	// Спросить нужно ли сохранять
	int AskSave() {
		cout << endl;
		cout << "Хотите сохранить в файл?" << endl;
		return YesNo();

	}

	// Изменение цвета
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
			cout << "Введите размер квадратной матрицы (от 2 до 5): ";
			sizeMatrix = IntegerCheck(2, 5);
		}
		else {
			cout << "Введите размер квадратной матрицы (от 2 до 50): ";
			sizeMatrix = IntegerCheck(2, 50);
		}

		
		Matrix arr = Matrix(sizeMatrix);

		if (inputMethod == ManualInput) {
			cout << "Вводите матрицу (Каждый символ с новой строки от 1 до 90000): " << endl;
			arr.ManualInputFun(choiceFilling);
			cout << "Вы ввели: " << endl;
			arr.OutputScreen();

		}

		if (inputMethod == AutoInput) {
			cout << "Введите начальный символ (от 1 до 90000): " << endl;
			int startNum = IntegerCheck(1, 90000);
			arr.AutoInputFun(startNum, choiceFilling);
			cout << "Вы ввели: " << endl;
			arr.OutputScreen();


		}

		if (inputMethod == RandomInput) {
			arr.RandomInputFun();
			cout << "Зелёным цветом выделены натуральные числа" << endl;
			cout << "Вы ввели: " << endl;
			arr.OutputScreen();


		}
		string output = "";
		if (AskSave() == Yes) {
			arr.SaveToFile(SaveArray, output);
		}

		cout << endl << "Результат: " << endl;



		arr.HorizontallyChecking(output);
		arr.VerticallyChecking(output);
		arr.DiagonalCheckingDownLeft(output);
		arr.DiagonalCheckingUpRight(output);

		cout << output << endl;

		if (AskSave() == Yes) {
			arr.SaveToFile(SaveResult, output);
		}
	}



	// Пользовательский выбор способа запонения матрицы
	void UserСhoice(int inputMethod) {


		cout << "Выберите способ заполнения матрицы:" << endl;
		cout << "1. Змейка." << endl;
		cout << "2. Улитка." << endl;
		cout << endl << "Ваш выбор: ";

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

	// Главное меню
	bool MainMenu(bool сhoice) {
		if (сhoice) {
			cout << "1. Начать работу." << endl;
		}

		else {
			cout << endl << "Попробовать еще раз?" << endl;
			cout << "1. Начать заново" << endl;
		}

		cout << "2. Выход." << endl << endl;
		cout << "Ваш выбор: ";
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
			cout << "1. Ручной ввод." << endl;
			cout << "2. Автоматическое заполнение." << endl;
			cout << "3. Случайное заполнение." << endl;
			cout << "4. Ввод из файла." << endl;

			cout << endl << "Ваш выбор: ";

			int const NumberItemsMin = 1;
			int const NumberItemsMax = 4;
			switch (IntegerCheck(NumberItemsMin, NumberItemsMax)) {
			case(ManualInput):
				UserСhoice(ManualInput);
				break;
			case(AutoInput):
				UserСhoice(AutoInput);
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


