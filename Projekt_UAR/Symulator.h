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
	double arx_val = 0;
	double pid_val = 0;
	double gen_val = 0;
	typ_generatora typ_gen = typ_generatora::gen_Skok;
	int iteration = 0;
public:
	Symulator(std::vector<double> A, std::vector<double> B,int opoznienie,bool zaklocenia,double proporcja,double calka, double rozniczka,double amplituda, int okres, int zapelnienie) 
		:arx(A,B,opoznienie,zaklocenia),pid(proporcja,calka,rozniczka),gen(amplituda,okres,zapelnienie)
	{};
	void set_generator_type(typ_generatora typ);
	void set_arx(std::vector<double> A, std::vector<double> B, int opoznienie, bool zaklocenia);
	void set_pid(double proporcja, double calka, double rozniczka);
	void set_gen(double amplituda, int okres, int zapelnienie);
	void iterate();
	double simulate() {};
};