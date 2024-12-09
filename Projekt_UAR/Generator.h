#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "Wybor.h"

class Generator 
{
private:
	int T = 0;
	int iteration = 0;
	double Amp = 0;
	int fill = 0;
public:
	Generator() {};
	void set_T(int T_val);
	void set_Amp(double Amp_val);
	void set_fill(double fill_val);
	void Iterate();
	int get_T();
	double get_Amp();
	int get_Iteration();
	double get_fill();
	double Generate_SKOK();
	double Generate_SIN();
	double Generate_SYG();
};

