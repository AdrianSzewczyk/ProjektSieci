#pragma once
#include <vector>
#include <queue>
#include <numeric> 
class model_ARX 
{
private:
	int iteration = 0;
	double y_output = 0;
	int input_buffer_size = 0;
	std::vector<double> values_A;
	std::vector<double> values_B;
	std::deque<double> buffer_input;
	std::deque<double> buffer_error_u;
	std::deque<double> buffer_output_y;
public:
	void Iterate();
	double Simulate(double pid_val);
	model_ARX(std::vector<double> A, std::vector<double> B, int inp)
	{
		values_A = A;
		values_B = B;
		input_buffer_size = inp;
	}
	model_ARX() = delete;
};