#include "Modele.h"


void Model_ARX::dodaj(Model* mod) 
{
	m_modele.push_back(mod);
}

void Model_ARX::operacja(Symulacja& sym) const
{
	int op = sym.get_dane_wej();
	op = op / 2;
	sym.set_dane_wyj(op);
}
void Model_ARX::wywolaj(Symulacja& sym)
{
	for(Model* var : m_modele)
	{
		var->operacja(sym);
	}
	this->operacja(sym);
}
void Model_Generator::operacja(Symulacja& sym) const
{
	int op = 1;
	sym.set_dane_wej(op);
}

void Model_PID::operacja(Symulacja& sym) const
{
	int op = sym.get_dane_wej();
	op = op * 4;
	sym.set_dane_wej(op);
}