#pragma once
#include "ARX.h"
#include "PID.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "Wybor.h"

// Funkcje pomocnicze do raportowania b³êdów
void raportBledu(const std::vector<double>& spodziewany, const std::vector<double>& faktyczny);
bool porownajSekwencje(const std::vector<double>& spodziewany, const std::vector<double>& faktyczny, double tolerancja = 0.1);

class TestPID {
public:
    static void test_PID_skokJednostkowy();  // Test skoku jednostkowego
};
class TestARX {
public:
    static void test_ARX_skokJednostkowy();
};