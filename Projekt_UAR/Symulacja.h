#pragma once
#include <iostream>
class Symulacja
{
private:
	int dane_wejsciowe = 0;
	int dane_wyjsciowe = 1;
public:
	void set_dane_wej(int wart)
	{
		dane_wejsciowe = wart;
	}
	void set_dane_wyj(int wart)
	{
		dane_wyjsciowe = wart;
	}
	int get_dane_wej()
	{
		return dane_wejsciowe;
	}
	int get_dane_wyj()
	{
		return dane_wejsciowe;
	}

	friend std::ostream& operator<<(std::ostream& str, const Symulacja& Symulacja)
	{
		str << "Dane wej: " << Symulacja.dane_wejsciowe << " " << "Dane wyj: " << Symulacja.dane_wyjsciowe;
		return str;
	}
};
