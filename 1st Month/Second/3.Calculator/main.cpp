#include "calculator.h"
#include "Printer.h"

int main() {
	Calculator calculator;

	std::cout << "3+5=" << calculator.Add(3, 5) << '\n';
	std::cout << "3/5=" << calculator.Divide(3, 5) << '\n';
	std::cout << "12-7=" << calculator.Substract(12, 7) << '\n';
	std::cout << "12x7=" << calculator.Multiply(12, 7) << '\n';
	std::cout << "15x7=" << calculator.Multiply(15, 7) << '\n';

	calculator.ShowOperationCount();

	std::cin.get();

	return 0;
}