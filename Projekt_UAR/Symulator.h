#pragma once
#include "ARX.h"
#include "PID.h"
#include "Generator.h"
enum typ_generatora
{
	gen_Skok,
	gen_Sin,
	gen_Syg
};
class Symulator 
{
	model_ARX arx;
	PID_controller pid;
	Generator gen;
	typ_generatora typ_gen;
public:
	Symulator();
	double simulate() {};
};