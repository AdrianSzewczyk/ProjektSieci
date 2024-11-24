#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
class PID_controller 
{
private:
	double k = 0; //amplification
	double Ti = 0; //integral constant
	double Td = 0; //derivative constant
	std::vector<double> Diff = {}; //all errors container;
	double Diff_now = 0; //error now
	double Diff_prev = 0; //error before
	int iteration = 0;
	double Output = 0;
public:
	PID_controller() {};
	void set_k(double k_val);
	void set_Ti(double Ti_val);
	void set_Td(double Td_val);
	double get_k();
	double get_Ti();
	double get_Td();
	void iterate();

	double proportional_control();
	double integral_control();
};