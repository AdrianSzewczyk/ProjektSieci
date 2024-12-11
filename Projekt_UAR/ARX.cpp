#include "ARX.h"
double model_ARX::Simulate(double pid_val)
{
	double dis = 0;
	if (disruption == true) 
	{
		
		std::normal_distribution<double> normal_dist_new(0, 0.01); 
		dis = normal_dist_new(rng);
	}
	if (buffer_input.size() == input_buffer_size)
	{
		buffer_error_u.push_back(buffer_input.front());
		buffer_input.pop_front();
	}
	buffer_input.push_back(pid_val);
	double inner_product_uB = 0;
	double inner_product_yA = 0;
	bool u_con = buffer_error_u.size() == values_B.size();
	bool y_con = buffer_output_y.size() == values_A.size();
	if(u_con)
	{
		inner_product_uB = std::inner_product(buffer_error_u.begin(), buffer_error_u.end(),values_B.rbegin(),0.0);
		buffer_error_u.pop_front();
	}
	if (y_con)
	{
		inner_product_yA = std::inner_product(buffer_output_y.begin(), buffer_output_y.end(), values_A.rbegin(), 0.0);
		buffer_output_y.pop_front();
	}
	
	y_output = (inner_product_uB - inner_product_yA) + dis;
	buffer_output_y.push_back(y_output);
	Iterate();
	return y_output;
};

void model_ARX::Iterate()
{
	iteration++;
};