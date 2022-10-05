#pragma once
#include <string>
namespace Menu {
	void Greeting();
	int AskSave();
	int YesNo();
	void ColorChange(std::string text, int color);
	int IntegerCheck(const int& min, const int& max);
	bool MainProgram(bool check);
	bool MainMenu(bool ñhoice);
}