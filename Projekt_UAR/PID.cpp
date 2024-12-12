#include "PID.h"

void PID_controller::set_k(double k_val)
{
	this->k = k_val;
}

void PID_controller::set_Ti(double Ti_val)
{
	this->Ti = Ti_val;
}

void PID_controller::set_Td(double Td_val)
{
	this->Td = Td_val;
}

double PID_controller::get_k()
{
	return this->k;
}

double PID_controller::get_Ti()
{
	return this->Ti;
}

double PID_controller::get_Td()
{
	return this->Td;
}

void PID_controller::iterate()
{
	iteration++;
}
void PID_controller::set_arx_output(double arx_val)
{
	this->arx_output = arx_val;
};
void PID_controller::set_generator_output(double gen_val)
{
	this->generator_output = gen_val;
};
double PID_controller::get_pid_output()
{
	return this->pid_Output;
}

double  PID_controller::proportional_control()
{
	double out = k * Diff_now;
	return out;
}

double PID_controller::integral_control()
{
	if (Ti == 0) return 0.0;
	else 
	{
	double out;
	diff_sum = diff_sum + Diff_now;
	
	out = diff_sum / Ti;
	return out;
	}
}

double PID_controller::derivative_control()
{
	double eq = (Diff_now - Diff_prev);
	double out = Td * eq;
	return out;
}

double PID_controller::simulate(double gen_val)
{
	error_calculation(gen_val);
	double prop = proportional_control();
	double integral = integral_control();
	double derivative = derivative_control();

	double out = prop + integral + derivative;
	pid_Output = out;
	iterate();
	return out;
}

double PID_controller::error_calculation(double gen_val)
{
	generator_output = gen_val;
	double diff = generator_output - arx_output;
	Diff_prev = Diff_now;
	Diff_now = diff;
	return diff;
};

void PID_controller::reset_Intergral() 
{
	Diff = { 0 };
};
void PID_controller::reset_Derivative() 
{
	Diff_prev = 0;
};