#include <iostream>

namespace PrimeNumber {
	//Малая теорема Ферма?? Походу она не работает
	/*
	Если p — простое число и a — целое число,
	не делящееся на p, то (a^(p-1))-1  делится на p.
	*/
	int CheckingTheNumber(int num) {
		if(num <= 3)
			return 1;
		for (int i = 2; i <= sqrt(num); i++) if ((num%i) == 0) return 0;
		return 1;
	}
}