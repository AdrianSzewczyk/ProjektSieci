#include "Symulator.h"

void Symulator::set_generator_type(typ_generatora typ) 
{
	typ_gen = typ;
};
void Symulator::set_arx(std::vector<double> A, std::vector<double> B, int opoznienie, bool zaklocenia) 
{
	arx.set_vector_A(A);
	arx.set_vector_B(B);
	arx.set_latency(opoznienie);
	arx.set_disruption_status(zaklocenia);
};
void Symulator::set_pid(double proporcja, double calka, double rozniczka) 
{
	pid.set_k(proporcja);
	pid.set_Ti(calka);
	pid.set_Td(rozniczka);
};
void Symulator::set_gen(double amplituda, int okres, int zapelnienie) 
{
	gen.set_Amp(amplituda);
	gen.set_T(okres);
	gen.set_fill(zapelnienie);
};
void Symulator::iterate() 
{
	iteration++;
};

double Symulator::simulate() {};