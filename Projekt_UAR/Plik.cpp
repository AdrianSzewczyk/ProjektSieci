#include "Plik.h"
void Plik::set_sym(Symulator* sym_addr)
{
	sym = sym_addr;
};
void Plik::free_sym() 
{
	sym = nullptr;
};
void Plik::save_config() 
{
	if (sym != nullptr)
	{
		model_ARX* arx_t = sym->get_arx();
		PID_controller* pid_t = sym->get_pid();
		Generator* gen_t = sym->get_gen();
		std::vector<double> write_A = arx_t->get_vector_A();
		std::vector<double> write_B = arx_t->get_vector_B();
		int write_latency = arx_t->get_latency();
		bool write_disuption = arx_t->get_disruption_status();

		double write_P = pid_t->get_k();
		double write_I = pid_t->get_Ti();
		double write_D = pid_t->get_Td();

		double write_Amp = gen_t->get_Amp();
		int write_T = gen_t->get_T();
		int write_fill = gen_t->get_fill();
		std::ofstream file("config.txt");
		if (file.is_open())
		{
			for (double val : write_A)
			{
				file << val << ";";
			}
			file << std::endl;
			for (double val : write_B)
			{
				file << val << ";";
			}
			file << std::endl;
			file << write_latency << std::endl;
			file << write_disuption << std::endl;
			file << write_P << std::endl;
			file << write_I << std::endl;
			file << write_D << std::endl;
			file << write_Amp << std::endl;
			file << write_T << std::endl;
			file << write_fill << std::endl;
			file.close();
		}
	}
};
void Plik::read_config() 
{

};

void Plik::save_config_bin()
{

};
void Plik::read_config_bin()
{

};