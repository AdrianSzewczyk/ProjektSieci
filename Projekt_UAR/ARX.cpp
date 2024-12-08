#include "ARX.h"
double model_ARX::Simulate(double pid_val)
{
	buffer_error_u.push_back(pid_val);
	
	double inner_product_uB = 0;
	double inner_product_yA = 0;
	bool u_con = buffer_error_u.size() >= values_B.size();
	bool y_con = buffer_output_y.size() >= values_A.size();
	if(u_con)
	{
		inner_product_uB = std::inner_product(buffer_error_u.begin(), buffer_error_u.end(),values_B.begin(),0.0);
		buffer_error_u.pop_front();
	}
	if (y_con)
	{
		inner_product_yA = std::inner_product(buffer_error_u.begin(), buffer_error_u.end(), values_A.begin(), 0.0);
		buffer_output_y.pop_front();
	}
	//if(u_con && y_con) 
	y_output = inner_product_uB - inner_product_yA;
	buffer_output_y.push_back(y_output);
	return y_output;
};

void model_ARX::Iterate()
{
	iteration++;
};