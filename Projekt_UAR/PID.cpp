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
	double out = 0;
	Diff.push_back(Diff_now);
	for (int i = 0; i < Diff.size(); i++)
	{
		out = out + Diff[i];
	}
	out = out / Ti;
	return out;
	}
}

double PID_controller::derivative_control()
{
	double eq = (Diff_now - Diff_prev);
	double out = Td * eq;
	return out;
}

double PID_controller::PID_control()
{
	double prop = proportional_control();
	double integral = integral_control();
	double derivative = derivative_control();

	double out = prop + integral + derivative;
	iterate();
	return out;
}