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
	double generator_output = 0;
	int iteration = 0;
	double pid_Output = 0;
	double arx_output = 0;
public:
	PID_controller() {};
	void set_k(double k_val);
	void set_Ti(double Ti_val);
	void set_Td(double Td_val);
	void set_arx_output(double arx_val);
	void set_generator_output(double gen_val);
	double get_k();
	double get_Ti();
	double get_Td();
	double get_pid_output();
	void iterate();
	
	double proportional_control();
	double integral_control();
	double derivative_control();
	double error_calculation(double gen_val);
	double PID_control(double gen_val);
};