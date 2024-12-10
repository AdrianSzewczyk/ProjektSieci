#include "Symulator.h"

void Symulator::set_generator_type(typ_generatora typ) {};
void Symulator::set_arx(std::vector<double> A, std::vector<double> B, int opoznienie, bool zaklocenia) {};
void Symulator::set_pid(double proporcja, double calka, double rozniczka) {};
void Symulator::set_gen(double amplituda, int okres, int zapelnienie) {};
void Symulator::iterate() {};

double Symulator::simulate() {};