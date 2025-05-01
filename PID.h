#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include "Wybor.h"

class PID_controller 
{
private:
	double k = 0; //amplification
	double Ti = 0; //integral constant
	double Td = 0; //derivative constant
	double diff_sum = 0;
	double Diff_now = 0; //error now
	double Diff_prev = 0; //error before
	double generator_output = 0;
	int iteration = 0;
	double pid_Output = 0;
    double p_output = 0;
    double i_output = 0;
    double d_output = 0;
	double arx_output = 0;
    bool tryb_I = false;
public:
	PID_controller(double k_val, double Ti_val, double Td_val) 
	{
		k = k_val;
		Ti = Ti_val;
		Td = Td_val;
	};
	PID_controller(double k_val)
	{
		k = k_val;
	};
	PID_controller(double k_val, double Ti_val)
	{
		k = k_val;
		Ti = Ti_val;
	};

    PID_controller();
    PID_controller(const PID_controller& other); // konstruktor kopiujący
    PID_controller& operator=(const PID_controller& other);

	void set_k(double k_val);
	void set_Ti(double Ti_val);
	void set_Td(double Td_val);
	void set_arx_output(double arx_val);
	void set_generator_output(double gen_val);
    void set_tryb_I(bool tryb);
	double get_k();
	double get_Ti();
	double get_Td();
	double get_pid_output();
    double get_diff();
    double get_p_out();
    double get_i_out();
    double get_d_out();
    bool get_tryb_I();
	void iterate();
    void reset();
	void reset_Intergral();
	void reset_Derivative();
	double proportional_control();
	double integral_control();
	double derivative_control();
	double error_calculation(double gen_val);
	double simulate(double gen_val);
	~PID_controller() {};
};
