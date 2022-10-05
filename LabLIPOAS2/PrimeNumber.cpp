#include <iostream>

namespace PrimeNumber {
	//����� ������� �����?? ������ ��� �� ��������
	/*
	���� p � ������� ����� � a � ����� �����,
	�� ��������� �� p, �� (a^(p-1))-1  ������� �� p.
	*/
	int CheckingTheNumber(int num) {
		if(num <= 3)
			return 1;
		for (int i = 2; i <= sqrt(num); i++) if ((num%i) == 0) return 0;
		return 1;
	}
}