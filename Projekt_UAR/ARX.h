#pragma once
#include <vector>
#include <queue>
class model_ARX 
{
private:
	int iteration = 0;
	std::vector<double> values_A;
	std::vector<double> values_B;
	std::queue<double> buffer_error_u;
	std::queue<double> buffer_simulate_y;
public:
	void Iterate();
	double Simulate();
};