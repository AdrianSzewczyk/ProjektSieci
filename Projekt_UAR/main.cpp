#include <iostream>
#include "Symulacja.h"
#include "Modele.h"

int main()
{
	Model_ARX model_arx;
	Model_Generator model_gen;
	Model_PID model_pid;
	model_arx.dodaj(&model_gen);
	model_arx.dodaj(&model_pid);
	Symulacja sym;
	std::cout << sym;
	std::cout << std::endl;
	model_arx.wywolaj(sym);
	std::cout << sym;
	std::cout << std::endl;
}