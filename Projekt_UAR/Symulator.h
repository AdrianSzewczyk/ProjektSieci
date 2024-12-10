#pragma once
#include "ARX.h"
#include "PID.h"
#include "Generator.h"
enum class typ_generatora
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
	typ_generatora typ_gen = typ_generatora::gen_Skok;
public:
	Symulator(std::vector<double> A, std::vector<double> B,int opoznienie,bool zaklocenia,double proporcja,double calka, double rozniczka,double amplituda, int okres, int zapelnienie) 
		:arx(A,B,opoznienie,zaklocenia),pid(proporcja,calka,rozniczka),gen(amplituda,okres,zapelnienie)
	{};
	void set_generator_type(typ_generatora typ);
	double simulate() {};
};