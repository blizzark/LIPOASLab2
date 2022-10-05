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
			int sizeMatrix = 2; // ������ �������
			int startNum = 1; // ��������� ����� ����������
			int choiceFilling = 1; // ����� ���������� -- ������

			int resultArray[2][2][2] = { {{1,1}, {2,1}}, {{4,0}, {3,1}} }; // ������ sizeMatrix*sizeMatrix. ������ ��������� ��� �������� �� �������������	

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
			int sizeMatrix = 3; // ������ �������
			int startNum = 101; // ��������� ����� ����������
			int choiceFilling = 2; // ����� ���������� -- ������

			int resultArray[3][3][2] = { {{101,1}, {102,0}, {103,1}}, {{108,0}, {109,1}, {104,0}}, {{107,1}, {106,0}, {105,0}} }; // ������ sizeMatrix*sizeMatrix. ������ ��������� ��� �������� �� �������������	

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
			int sizeMatrix = 2; // ������ �������
			int startNum = 1; // ��������� ����� ����������
			int choiceFilling = 1; // ����� ���������� -- ������


			string resultOutput = "�������������(�):\ny = a, (y = const)\n��� �: 1 = 100% (2��)\n��� �: 0 = 50% (1��)\n�����������(|):\nx = b, � = const\n��� b: 0 = 50% (1��)\n��� b: 1 = 100% (2��)\n�����������(/):\ny = � + b\n��� b = 1: 50% (1��)\n��� b = 0: 50% (1��)\n��� b = -1: 50% (1��)\n�����������(\\):\ny = -1 * � + b\n��� b = 2: 50% (1��)\n��� b = 1: 100% (2��)\n";
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