#include "ARX.h"
double model_ARX::Simulate(double pid_val)
{
	double dis = 0;
    if (disruption_amplitude>0)
	{
		
        std::normal_distribution<double> normal_dist_new(0, disruption_amplitude);
		dis = normal_dist_new(rng);
	}

    buffer_error_u.push_back(buffer_input.front());
    buffer_input.pop_front();

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

void model_ARX::set_vector_A(std::vector<double> A)
{
	values_A = A;
    while(buffer_output_y.size() > values_A.size()) buffer_output_y.pop_front();
    //buffer_output_y.pop_front();
};
void model_ARX::set_vector_B(std::vector<double> B)
{
	values_B = B;
    buffer_error_u = {};
};
void model_ARX::set_latency(int inp)
{
    if (inp < 1) inp = 1;
	input_buffer_size = inp;
    buffer_input.resize(inp,0);
};
void model_ARX::set_disruption_amplitude(double amp)
{
    disruption_amplitude = amp;
};

std::vector<double> model_ARX::get_vector_A()
{
	return values_A;
};
std::vector<double> model_ARX::get_vector_B()
{
	return values_B;
};
int model_ARX::get_latency() 
{
	return input_buffer_size;
};
double model_ARX::get_disruption_amplitude() const
{
    return disruption_amplitude;
};

void model_ARX::reset()
{
    iteration = 0;
    y_output = 0.0;
    // Wypełnij bufory zerami:
    buffer_input.assign(input_buffer_size,  0.0);
    buffer_error_u.assign(values_B.size(),   0.0);
    buffer_output_y.assign(values_A.size(),  0.0);
}
model_ARX::model_ARX(const model_ARX& o)
    : iteration(o.iteration),
    y_output(o.y_output),
    input_buffer_size(o.input_buffer_size),
    disruption_amplitude(o.disruption_amplitude),
    values_A(o.values_A),
    values_B(o.values_B),
    buffer_input(o.buffer_input),
    buffer_error_u(o.buffer_error_u),
    buffer_output_y(o.buffer_output_y),
    rng(o.rng)    // std::mt19937 jest kopiowalny
{}
model_ARX& model_ARX::operator=(const model_ARX& o) {
    if (this != &o) {
        iteration = o.iteration;
        y_output = o.y_output;
        input_buffer_size = o.input_buffer_size;
        disruption_amplitude = o.disruption_amplitude;
        values_A = o.values_A;
        values_B = o.values_B;
        buffer_input = o.buffer_input;
        buffer_error_u = o.buffer_error_u;
        buffer_output_y = o.buffer_output_y;
        rng = o.rng;
    }
    return *this;
}
