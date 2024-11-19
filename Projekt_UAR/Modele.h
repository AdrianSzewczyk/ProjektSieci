#pragma once
#include <vector>
#include <iostream>
#include "Symulacja.h"
class Model
{
public:
	virtual void operacja(Symulacja& sym) const = 0;
};

class Model_ARX : public Model
{
private:
	std::vector<Model*> m_modele;
public:
	void dodaj(Model* mod);
	void operacja(Symulacja& sym) const override;
	void wywolaj(Symulacja& sym);
};

class Model_PID : public Model
{
public:
	void operacja(Symulacja& sym) const override;
};

class Model_Generator : public Model
{

public:
	void operacja(Symulacja& sym) const override;
};