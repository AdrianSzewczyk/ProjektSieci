#include <iostream>
#include "Generator.h"
#include "PID.h"
#include "ARX.h"
#ifdef MAIN



int main()
{
	Generator gen;
	std::vector<double> a = { -0.4 };
	std::vector<double> b = { 0.6 };
	PID_controller pid(1.02, 10, 0.3);
	model_ARX arx(a,b);
	gen.set_Amp(1);
	gen.set_T(1);
	double generator = 0;
	double pid_output = 0;
	double ARX_OUTPUT = 0;
	for (int i = 0; i < 200; i++)
	{
		generator = gen.Generate_SKOK();
		pid_output = pid.PID_control(generator);
		ARX_OUTPUT = arx.Simulate(pid_output);
		pid.set_arx_output(ARX_OUTPUT);
		std::cerr<< generator << " " << pid_output << " " << ARX_OUTPUT << std::endl;
	}
}
#endif // MAIN