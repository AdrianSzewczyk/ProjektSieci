#pragma once
#include "Symulator.h"
#include <fstream>
class Plik 
{
private:
	Symulator* sym = nullptr;
public:
	Plik() {};

	void save_config();
	void read_config();

	void save_config_bin();
	void read_config_bin();

	~Plik() {};
};