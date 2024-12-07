#include <iostream>
#include "Generator.h"
#include "PID.h"
#include "ARX.h"
int main()
{
	PID_controller pid;
	pid.set_arx_output(0);
	pid.set_generator_output(3);
	pid.set_k(1);
	pid.set_Td(1);
	pid.set_Ti(1);
	pid.PID_control();
	std::cout << pid.get_pid_output();
}