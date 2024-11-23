#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

class Generator 
{
private:
	int T = 2;
	int iteration = 0;
	double Amp = 1;
public:
	Generator() {};
	void set_T(int T_val);
	void set_Amp(double Amp_val);
	void Iterate();
	int get_T();
	double get_Amp();
	int get_Iteration();
	virtual double Generate() { return 0; };
};

class Generator_SKOK : public Generator
{
private:

public:
	double Generate() override;
};

class Generator_SIN : public Generator
{
private:

public:
	double Generate() override;
};

class Generator_SYG : public Generator
{
private:
	double fill = 0;
public:
	void set_fill(double fill_val);
	double get_fill();
	double Generate() override;
};