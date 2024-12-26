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
		std::cout << "µ¡¼À: " << countAdd << '\t'
			<< "»¬¼À: " << countSubstract << '\t'
			<< "°ö¼À: " << countMultiply << '\t'
			<< "³ª´°¼À: " << countDivide << '\n';
	}

private:
	int countAdd = 0;
	int countDivide = 0;
	int countSubstract = 0;
	int countMultiply = 0;
};