#include <iostream>
#include "Symulator.h"
#include "Plik.h"
#ifdef MAIN



int main()
{
	Symulator sym({ -0.4 }, { 0.6 }, 1, 1,1,10,1,1,1,1);
	//Symulator sym;
	Plik plik;
	plik.set_sym(&sym);
	//plik.read_config();
	//plik.save_config_bin();
	plik.read_config_bin();
	
	for (int i = 0; i < 100; i++)
	{
		std::cout<<sym.simulate()<<std::endl;
	}
	
}
#endif // MAIN