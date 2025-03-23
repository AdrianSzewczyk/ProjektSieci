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
void PID_controller::set_tryb_I(bool tryb)
{
    this->tryb_I = tryb;
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
double PID_controller::get_diff()
{
    return this->Diff_now;
}
bool  PID_controller::get_tryb_I()
{
    return this->tryb_I;
}

double  PID_controller::proportional_control()
{
    p_output = k * Diff_now;
    return p_output;
}

double PID_controller::integral_control()
{
	if (Ti == 0) return 0.0;
	else 
	{
    if(tryb_I)
    {
    diff_sum = diff_sum + (Diff_now/Ti);
    return diff_sum;
    }
    else
    {
	diff_sum = diff_sum + Diff_now;
    i_output = (diff_sum / Ti);
    return i_output;
    }
	}
}

double PID_controller::derivative_control()
{
    d_output = Td * (Diff_now - Diff_prev);
    return d_output;
}

double PID_controller::simulate(double gen_val)
{
	error_calculation(gen_val);
	double out = proportional_control() + integral_control() + derivative_control();
	pid_Output = out;
	iterate();
	return out;
}

double PID_controller::error_calculation(double gen_val)
{
	double diff = gen_val - arx_output;
	Diff_prev = Diff_now;
	Diff_now = diff;
	return diff;
};

double PID_controller::get_p_out()
{
return p_output;
};
double PID_controller::get_i_out()
{
    if(tryb_I)
    {
        return diff_sum;
    }
    else
    {
        return i_output;
    }
};
double PID_controller::get_d_out()
{
return d_output;
};
void PID_controller::reset()
{
    p_output = 0;
    i_output= 0;
    d_output = 0;
    pid_Output =0;
    arx_output = 0;
};
void PID_controller::reset_Intergral() 
{
	diff_sum = { 0 };
};
void PID_controller::reset_Derivative() 
{
    Diff_now = 0;
	Diff_prev = 0;
};
