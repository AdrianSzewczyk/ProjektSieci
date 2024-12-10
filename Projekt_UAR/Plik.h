#pragma once
#include "Symulator.h"
#include <fstream>
#include <sstream>
#include <string>
class Plik 
{
private:
	Symulator* sym = nullptr;
public:
	Plik() {};
	void set_sym(Symulator* sym_addr);
	void free_sym();

	void save_config();
	void read_config();

	void save_config_bin();
	void read_config_bin();

	~Plik() {};
};