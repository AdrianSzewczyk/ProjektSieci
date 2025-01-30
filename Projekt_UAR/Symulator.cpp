#include "Symulator.h"

void Symulator::set_generator_type(typ_generatora typ) 
{
	typ_gen = typ;
};
void Symulator::set_arx(std::vector<double> A, std::vector<double> B, int opoznienie, bool zaklocenia) 
{
	arx.set_vector_A(A);
	arx.set_vector_B(B);
	arx.set_latency(opoznienie);
	arx.set_disruption_status(zaklocenia);
};
void Symulator::set_pid(double proporcja, double calka, double rozniczka) 
{
	pid.set_k(proporcja);
	pid.set_Ti(calka);
	pid.set_Td(rozniczka);
};
void Symulator::set_gen(double amplituda, int okres, double zapelnienie)
{
	gen.set_Amp(amplituda);
	gen.set_T(okres);
	gen.set_fill(zapelnienie);
};
void Symulator::iterate() 
{
	iteration++;
};
model_ARX* Symulator::get_arx()
{
	return &arx;
};
PID_controller* Symulator::get_pid()
{
	return &pid;
};
Generator* Symulator::get_gen()
{
	return &gen;
};
double Symulator::get_gen_val()
{
    return gen_val;
};
double Symulator::get_pid_val()
{
    return pid_val;
};
double Symulator::get_arx_val()
{
    return arx_val;
};
int Symulator::get_iteration()
{
    return iteration;
};
double Symulator::simulate() 
{
	switch (typ_gen)
	{
	case typ_generatora::gen_Skok:
		gen_val = gen.Generate_SKOK();
		break;
	case typ_generatora::gen_Sin:
		gen_val = gen.Generate_SIN();
		break;
	case typ_generatora::gen_Syg:
		gen_val = gen.Generate_SYG();
		break;
	default:
		gen_val = gen.Generate_SKOK();
		break;
	}
	pid_val = pid.simulate(gen_val);
	arx_val = arx.Simulate(pid_val);
	pid.set_arx_output(arx_val);
	iterate();
	return arx_val;
};

void Symulator::save_config()
{
        std::vector<double> write_A = get_arx()->get_vector_A();
        std::vector<double> write_B = get_arx()->get_vector_B();
        int write_latency = get_arx()->get_latency();
        bool write_disuption = get_arx()->get_disruption_status();

        double write_P = get_pid()->get_k();
        double write_I = get_pid()->get_Ti();
        double write_D = get_pid()->get_Td();

        double write_Amp = get_gen()->get_Amp();
        int write_T = get_gen()->get_T();
        double write_fill = get_gen()->get_fill();
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

};
void Symulator::read_config()
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
        std::ifstream file("config.txt",std::ifstream::in);
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
            set_arx(values_read_A, values_read_B, latency_read, disruption_read);
            std::getline(file, str);
            P_read = std::stod(str);
            std::getline(file, str);
            I_read = std::stod(str);
            std::getline(file, str);
            D_read = std::stod(str);
            set_pid(P_read, I_read, D_read);
            std::getline(file, str);
            k_read = std::stod(str);
            std::getline(file, str);
            T_read = std::stoi(str);
            std::getline(file, str);
            fill_read = std::stod(str);
            set_gen(k_read, T_read, fill_read);
            file.close();
        }

};

void Symulator::save_config_bin()
{

        std::vector<double> write_A = get_arx()->get_vector_A();
        std::vector<double> write_B = get_arx()->get_vector_B();
        int write_latency = get_arx()->get_latency();
        bool write_disuption = get_arx()->get_disruption_status();

        double write_P = get_pid()->get_k();
        double write_I = get_pid()->get_Ti();
        double write_D = get_pid()->get_Td();

        double write_Amp = get_gen()->get_Amp();
        int write_T = get_gen()->get_T();
        double write_fill = get_gen()->get_fill();
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

};
void Symulator::read_config_bin()
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
        set_arx(read_A, read_B, read_latency, read_disruption);
        set_pid(read_P, read_I, read_D);
        set_gen(read_Amp, read_T, read_fill);

};
