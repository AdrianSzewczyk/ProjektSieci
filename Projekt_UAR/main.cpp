#include <iostream>
#include "Symulator.h"
#include "Plik.h"
#ifdef MAIN



int main()
{
	Symulator sym({ -0.4 }, { 0.6 }, 1, 1,1,10,0.5,1,1,1);
	Plik plik;
	plik.set_sym(&sym);
	plik.save_config();
	for (int i = 0; i < 100; i++)
	{
		std::cout<<sym.simulate()<<std::endl;
	}
}
#endif // MAIN