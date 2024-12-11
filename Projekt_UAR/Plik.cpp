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
		double write_fill = gen_t->get_fill();
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
	if (sym != nullptr)
	{ 
		std::stringstream ss;
		std::string str;
		std::string temp;
		double val_d;
		std::vector<double> values_read_A;
		std::vector<double> values_read_B;
		int latency_read;
		bool disruption_read;
		double P_read;
		double I_read;
		double D_read;
		double k_read;
		int T_read;
		double fill_read;
		std::ifstream file("config.txt");
		if(file.is_open())
		{
			std::getline(file, str);
			ss << str;
			while(!ss.eof())
			{
				ss >> temp;
				if(std::stringstream(temp)>>val_d)
				{
				values_read_A.push_back(val_d);
				
				}
			}
			std::cout << std::endl;
			ss.clear();
			std::getline(file, str);
			ss << str;
			while (!ss.eof())
			{
				ss >> temp;
				if (std::stringstream(temp) >> val_d)
				{
					values_read_B.push_back(val_d);
				}
			}
			std::getline(file, str);
			latency_read = std::stoi(str);
			str = "";
			std::getline(file, str);
			disruption_read = std::stoi(str);
			sym->set_arx(values_read_A, values_read_B, latency_read, disruption_read);
			std::getline(file, str);
			P_read = std::stod(str);
			std::getline(file, str);
			I_read = std::stod(str);
			std::getline(file, str);
			D_read = std::stod(str);
			sym->set_pid(P_read, I_read, D_read);
			std::getline(file, str);
			k_read = std::stod(str);
			std::getline(file, str);
			T_read = std::stoi(str);
			std::getline(file, str);
			fill_read = std::stod(str);
			sym->set_gen(k_read, T_read, fill_read);
			file.close();
		}
	}
};

void Plik::save_config_bin()
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
		double write_fill = gen_t->get_fill();
		int size_A = write_A.size();
		int size_B = write_B.size();
		std::ofstream file("config_bin.txt",std::ios::binary);
		if (file.is_open())
		{
			file.write(reinterpret_cast<char*>(&size_A), 1 * sizeof(int));
			for (double val : write_A)
			{
				file.write(reinterpret_cast<char*>(&val), 1 * sizeof(double));
			}
			file.write(reinterpret_cast<char*>(&size_B), 1 * sizeof(int));
			for (double val : write_B)
			{
				file.write(reinterpret_cast<char*>(&val), 1 * sizeof(double));
			}
			file.write(reinterpret_cast<char*>(&write_latency), 1 * sizeof(int));
			file.write(reinterpret_cast<char*>(&write_disuption), 1 * sizeof(bool));
			file.write(reinterpret_cast<char*>(&write_P), 1 * sizeof(double));
			file.write(reinterpret_cast<char*>(&write_I), 1 * sizeof(double));
			file.write(reinterpret_cast<char*>(&write_D), 1 * sizeof(double));

			file.write(reinterpret_cast<char*>(&write_Amp), 1 * sizeof(double));
			file.write(reinterpret_cast<char*>(&write_T), 1 * sizeof(int));
			file.write(reinterpret_cast<char*>(&write_fill), 1 * sizeof(double));
			file.close();
		}
	}
};
void Plik::read_config_bin()
{
	if (sym != nullptr)
	{
	std::vector<double> read_A;
	std::vector<double> read_B;
	int read_latency;
	bool read_disruption;
	double temp_val;
	double read_P;
	double read_I;
	double read_D;

	double read_Amp;
	int read_T;
	double read_fill;

	int size_A;
	int size_B;
	std::ifstream file("config_bin.txt", std::ios::binary);
	if (file.is_open())
	{
	file.read(reinterpret_cast<char*>(&size_A), 1 * sizeof(int));
	for (int i = 0; i < size_A; i++)
	{
		file.read(reinterpret_cast<char*>(&temp_val), 1 * sizeof(double));
		read_A.push_back(temp_val);
	}
	file.read(reinterpret_cast<char*>(&size_B), 1 * sizeof(int));
	for (int i = 0; i < size_B; i++)
	{
		file.read(reinterpret_cast<char*>(&temp_val), 1 * sizeof(double));
		read_B.push_back(temp_val);
	}
	file.read(reinterpret_cast<char*>(&read_latency), 1 * sizeof(int));
	file.read(reinterpret_cast<char*>(&read_disruption), 1 * sizeof(bool));
	file.read(reinterpret_cast<char*>(&read_P), 1 * sizeof(double));
	file.read(reinterpret_cast<char*>(&read_I), 1 * sizeof(double));
	file.read(reinterpret_cast<char*>(&read_D), 1 * sizeof(double));

	file.read(reinterpret_cast<char*>(&read_Amp), 1 * sizeof(double));
	file.read(reinterpret_cast<char*>(&read_T), 1 * sizeof(int));
	file.read(reinterpret_cast<char*>(&read_fill), 1 * sizeof(double));
	file.close();
	}
	sym->set_arx(read_A, read_B, read_latency, read_disruption);
	sym->set_pid(read_P, read_I, read_D);
	sym->set_gen(read_Amp, read_T, read_fill);
	}
};