#pragma once
#include <vector>
#include <queue>
#include <numeric>
#include <iostream>
#include <random>
#include "Wybor.h"
class model_ARX 
{
private:
	int iteration = 0;
	double y_output = 0;
	int input_buffer_size = 1;
    double disruption_amplitude = 0.0;
	std::vector<double> values_A;
	std::vector<double> values_B;
	std::deque<double> buffer_input;
	std::deque<double> buffer_error_u;
	std::deque<double> buffer_output_y;
	std::random_device seed_rng;
	std::mt19937 rng;
public:
	void Iterate();
	double Simulate(double pid_val);
    model_ARX(std::vector<double> A, std::vector<double> B, int inp, double disruption_amp)
	{
		values_A = A;
		values_B = B;
		if (inp < 1) inp = 1;
		input_buffer_size = inp;
        //buffer_input.resize(input_buffer_size);
        //buffer_error_u.resize(values_B.size());
        //buffer_output_y.resize(values_A.size());
        disruption_amplitude = disruption_amp;
		rng.seed(seed_rng());
	}
	model_ARX() = delete;
	void set_vector_A(std::vector<double> A);
	void set_vector_B(std::vector<double> B);
	void set_latency(int inp);
    void set_disruption_amplitude(double amp);
    void reset();
	std::vector<double> get_vector_A();
	std::vector<double> get_vector_B();
	int get_latency();
    double get_disruption_amplitude() const;
	~model_ARX() {};
};
