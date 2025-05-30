#include "Symulator.h"
#include <qdebug.h>

void Symulator::set_generator_type(typ_generatora typ) 
{
	typ_gen = typ;
};
void Symulator::set_arx(std::vector<double> A, std::vector<double> B, int opoznienie, double zaklocenia)
{
	arx.set_vector_A(A);
	arx.set_vector_B(B);
	arx.set_latency(opoznienie);
    arx.set_disruption_amplitude(zaklocenia);
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
void Symulator::reset()
{
    this->gen_val = 0;
    this->pid_val = 0;
    this->arx_val = 0;
    this->arx.reset();
    this->pid.reset_Derivative();
    this->pid.reset_Intergral();
    this->pid.reset();
    this->gen.reset();
}
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



double Symulator::SymulacjaTrybSieciowy(double obieWyj) {
    // 1) generator

    switch (typ_gen) {
    case typ_generatora::gen_Skok: gen_val = gen.Generate_SKOK(); break;
    case typ_generatora::gen_Sin:  gen_val = gen.Generate_SIN();  break;
    case typ_generatora::gen_Syg:  gen_val = gen.Generate_SYG();  break;
    }

    // 2) regulator PID — podajemy mu dwa wejścia: sygnał sterujący GEN i odbiór z procesu
    pid.set_arx_output(obieWyj);
    pid_val = pid.simulate(gen_val);

    // 3) wewnętrzny model ARX
    arx_val = arx.Simulate(pid_val);

    // 4) zwracamy wyjście symulatora‑ARX jako nowe "obieWyj"
    return arx_val;
}

void Symulator::setARXsieciowy(const std::vector<double>& A,
                        const std::vector<double>& B,
                        int opoznienie,
                        double zaklocenia)
{
    // Przypisujemy nowy obiekt ARX
    //arx = model_ARX(A, B, opoznienie, zaklocenia);

    // Jeśli chcesz od razu wyczyścić bufor wewnętrzny ARX:
    //arx.reset();
}



double Symulator::SymulacjaGeneratorRegulator() {
    // 1) generate
    switch (typ_gen) {
    case typ_generatora::gen_Skok: gen_val = gen.Generate_SKOK(); break;
    case typ_generatora::gen_Sin:  gen_val = gen.Generate_SIN();  break;
    case typ_generatora::gen_Syg:  gen_val = gen.Generate_SYG();  break;
    }

    pid_val = pid.simulate(gen_val);
    iterate();
    return pid_val;
}

void Symulator::AktualizacjaObiektu(double wyjO) {

    pid.set_arx_output(wyjO);

    arx_val = wyjO;
}
Symulator::Symulator(const Symulator& other)
    : arx(other.arx)  // Kopiowanie obiektów
    , pid(other.pid)
    , gen(other.gen)
    , gen_val(other.gen_val)
    , pid_val(other.pid_val)
    , arx_val(other.arx_val)
    , iteration(other.iteration)
    , typ_gen(other.typ_gen)
{
    // Głębokie kopiowanie, jeśli to konieczne, np. jeśli obiekty są dynamicznie alokowane
    // np. jeśli masz dynamiczne zasoby (tablice, wektory, itp.)
    this->arx = other.arx;  // Należy upewnić się, że operator przypisania dla `arx` jest poprawnie zaimplementowany
    this->pid = other.pid;  // Podobnie jak powyżej dla PID
    this->gen = other.gen;  // I dla generatora
}

// Operator przypisania Symulator
Symulator& Symulator::operator=(const Symulator& other) {
    if (this != &other) {
        arx = other.arx;  // Kopiowanie obiektów
        pid = other.pid;
        gen = other.gen;
        gen_val = other.gen_val;
        pid_val = other.pid_val;
        arx_val = other.arx_val;
        iteration = other.iteration;
        typ_gen = other.typ_gen;
    }
    return *this;
}
