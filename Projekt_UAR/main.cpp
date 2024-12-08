#include <iostream>
#include "Generator.h"
#include "PID.h"
#include "ARX.h"
int main()
{
	Generator gen;
	std::vector<double> a = { 2.0,2.0 };
	std::vector<double> b = { 2.0,2.0 };
	model_ARX arx(a,b);
	gen.set_Amp(5);
	gen.set_T(0);
	double gene = 0;
	for (int i = 0; i < 10; i++)
	{
		gene = gen.Generate_SKOK();
		std::cerr<< arx.Simulate(gene)<<std::endl;
	}
}