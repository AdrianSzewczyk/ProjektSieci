#include <iostream>
#include "Generator.h"
int main()
{
	Generator_SKOK genSKOK;
	Generator_SIN genSIN;
	Generator_SYG genSYG;

	double amp = 1;
	int valT = 50;
	double fill = 0.9;

	genSKOK.set_Amp(amp);
	genSIN.set_Amp(amp);
	genSYG.set_Amp(amp);

	genSKOK.set_T(valT);
	genSIN.set_T(valT);
	genSYG.set_T(valT);

	genSYG.set_fill(fill);

	for (int i = 0; i < 100; i++)
	{
		std::cout <<"SKOK: "<< genSKOK.Generate() << std::endl;
	}

	for (int i = 0; i < 100; i++)
	{
		std::cout << "SIN: " << genSIN.Generate() << std::endl;
	}

	for (int i = 0; i < 100; i++)
	{
		std::cout << "SYG: " << genSYG.Generate() << std::endl;
	}
}