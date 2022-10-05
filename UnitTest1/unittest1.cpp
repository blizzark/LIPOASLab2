#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LabLIPOAS2/PrimeNumber.h"
#include "../LabLIPOAS2/PrimeNumber.Cpp"
#include "../LabLIPOAS2/Matrix.h"
#include "../LabLIPOAS2/Matrix.cpp"
#include "../LabLIPOAS2/Menu.cpp"
#include "../LabLIPOAS2/Menu.h"
#include "../LabLIPOAS2/FileWork.h"
#include "../LabLIPOAS2/FileWork.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace matrix;
namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethodCheckingTheNumber)
		{
			int number = 701;
			int result = 1;
			Assert::AreEqual(PrimeNumber::CheckingTheNumber(number), result);
		}
		TEST_METHOD(TestMethodMatrixSnake)
		{
			int sizeMatrix = 2; // Размер матрицы
			int startNum = 1; // Стартовое число заполнения
			int choiceFilling = 1; // Выбор заполнения -- змейка

			int resultArray[2][2][2] = { {{1,1}, {2,1}}, {{4,0}, {3,1}} }; // Размер sizeMatrix*sizeMatrix. Третье измерение для проверки на натуральность	

			Matrix arr = Matrix(sizeMatrix);
			arr.AutoInputFun(startNum, choiceFilling);
			for (size_t i = 0; i < sizeMatrix; i++)
			{
				for (size_t j = 0; j < sizeMatrix; j++)
				{
					for (size_t k = 0; k < 2; k++)
					{
						Assert::AreEqual(arr.GetArray()[i][j][k], resultArray[i][j][k]);
					}
				}
			}
		
		}
		TEST_METHOD(TestMethodMatrixSnail)
		{
			int sizeMatrix = 3; // Размер матрицы
			int startNum = 101; // Стартовое число заполнения
			int choiceFilling = 2; // Выбор заполнения -- улитка

			int resultArray[3][3][2] = { {{101,1}, {102,0}, {103,1}}, {{108,0}, {109,1}, {104,0}}, {{107,1}, {106,0}, {105,0}} }; // Размер sizeMatrix*sizeMatrix. Третье измерение для проверки на натуральность	

			Matrix arr = Matrix(sizeMatrix);
			arr.AutoInputFun(startNum, choiceFilling);
			for (size_t i = 0; i < sizeMatrix; i++)
			{
				for (size_t j = 0; j < sizeMatrix; j++)
				{
					for (size_t k = 0; k < 2; k++)
					{
						Assert::AreEqual(arr.GetArray()[i][j][k], resultArray[i][j][k]);
					}
				}
			}

		}
		TEST_METHOD(TestMethodMatrixPercent)
		{
			int sizeMatrix = 2; // Размер матрицы
			int startNum = 1; // Стартовое число заполнения
			int choiceFilling = 1; // Выбор заполнения -- улитка


			string resultOutput = "Горизонтально(—):\ny = a, (y = const)\nПри а: 1 = 100% (2шт)\nПри а: 0 = 50% (1шт)\nВертикально(|):\nx = b, х = const\nПри b: 0 = 50% (1шт)\nПри b: 1 = 100% (2шт)\nДиагонально(/):\ny = х + b\nПри b = 1: 50% (1шт)\nПри b = 0: 50% (1шт)\nПри b = -1: 50% (1шт)\nДиагонально(\\):\ny = -1 * х + b\nПри b = 2: 50% (1шт)\nПри b = 1: 100% (2шт)\n";
			string output{};
			
			Matrix arr = Matrix(sizeMatrix);
			arr.AutoInputFun(startNum, choiceFilling);

			arr.HorizontallyChecking(output);
			arr.VerticallyChecking(output);
			arr.DiagonalCheckingDownLeft(output);
			arr.DiagonalCheckingUpRight(output);
			
			Assert::AreEqual(resultOutput, output);
					
		}

	};
}