#include "Generator.h"

//setery i getery
void Generator::set_T(int T_val) 
{
	this->T = T_val;
};

void Generator::set_Amp(double Amp_val) 
{
	this->Amp = Amp_val;
};

void Generator::set_fill(double fill_val)
{
	if (fill_val > 1) fill_val = 1.0;
	this->fill = fill_val;
};

void Generator::Iterate()
{
	this->iteration = iteration+1;
};

int Generator::get_T()
{
	return this->T;
};

double Generator::get_Amp()
{
	return this->Amp;
};

int Generator::get_Iteration()
{
	return this->iteration;
};

double Generator::get_fill()
{
	return this->fill;
};

void Generator::reset()
{
    iteration = 0;
}




double Generator::Generate_SKOK()
{
	int val_T = get_T();
	int val_Ite = get_Iteration();
	if (val_Ite >= val_T)
	{
		Iterate();
		return get_Amp();
	}
	else
	{
		Iterate();
		return 0.0;
	};
};

double Generator::Generate_SIN()
{
	int val_T = get_T();
	if (val_T <= 0) val_T = 1;
	int val_I = get_Iteration();
	double val_Amp = get_Amp();

	double val_imodT = (double)(val_I % val_T)/val_T;
	double val_iTPI = val_imodT * 2.0 * M_PI;
	double val_ASin = val_Amp * sin(val_iTPI);
	Iterate();
	return val_ASin;
};

double Generator::Generate_SYG()
{
	int val_T = get_T();
	int val_Ite = get_Iteration();
	double val_fill = get_fill();
	double val_Amp = get_Amp();
	if (val_Ite%val_T < val_fill*val_T)
	{
		Iterate();
		return val_Amp;
	}
	else
	{
		Iterate();
		return 0.0;
	};
};
