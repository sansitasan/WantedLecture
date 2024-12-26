#pragma once
#include <iostream>

class Calculator {
public:
	Calculator() {}
	inline double Add(double a, double b)
	{
		++countAdd;
		return a + b;
	}

	inline double Divide(double a, double b)
	{
		++countDivide;
		return a / b;
	}

	inline double Substract(double a, double b)
	{
		++countSubstract;
		return a - b;
	}

	inline double Multiply(double a, double b)
	{
		++countMultiply;
		return a * b;
	}

	inline void ShowOperationCount() {
		std::cout << "����: " << countAdd << '\t'
			<< "����: " << countSubstract << '\t'
			<< "����: " << countMultiply << '\t'
			<< "������: " << countDivide << '\n';
	}

private:
	int countAdd = 0;
	int countDivide = 0;
	int countSubstract = 0;
	int countMultiply = 0;
};