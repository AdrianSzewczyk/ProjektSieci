#include <iostream>
#include "Symulator.h"
#ifdef MAIN



int main()
{
	Symulator sym({ -0.4 }, { 0.6 }, 1, 1,1,10,0.5,1,1,1);
	for (int i = 0; i < 100; i++)
	{
		std::cout<<sym.simulate()<<std::endl;
	}
}
#endif // MAIN