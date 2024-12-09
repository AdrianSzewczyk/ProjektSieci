#include "Test_PID_ARX.h"

// Funkcja pomocnicza do raportowania ró¿nic miêdzy oczekiwanymi a faktycznymi wynikami
void raportBledu(const std::vector<double>& spodziewany, const std::vector<double>& faktyczny) {
    std::cerr << "Spodziewany: ";
    for (const auto& val : spodziewany)
        std::cerr << val << " ";
    std::cerr << "\nFaktyczny: ";
    for (const auto& val : faktyczny)
        std::cerr << val << " ";
    std::cerr << std::endl;
}

// Funkcja porównuj¹ca dwie sekwencje z tolerancj¹ b³êdu
bool porownajSekwencje(const std::vector<double>& spodziewany, const std::vector<double>& faktyczny, double tolerancja) {
    if (spodziewany.size() != faktyczny.size())
        return false;

    for (size_t i = 0; i < spodziewany.size(); i++) {
        if (std::fabs(spodziewany[i] - faktyczny[i]) > tolerancja)
            return false;
    }

    return true;
}

void TestPID::test_PID_skokJednostkowy() {
    std::cerr << "Test PID: Reakcja na skok jednostkowy w chwili 1\n";

    try {
        PID_controller pid(1.0, 1.0, 1.0);  // Ustawienia PID
        constexpr size_t LICZ_ITER = 21;    // Liczba iteracji w symulacji
        std::vector<double> pobudzenie(LICZ_ITER, 0.0); // Pocz¹tkowo same zera (brak sygna³u)
        std::vector<double> spodziewane(LICZ_ITER);     // Spodziewane wyniki
        std::vector<double> faktyczne(LICZ_ITER);      // Faktyczne wyniki z symulacji

        // Skok jednostkowy w chwili 1
        for (size_t i = 1; i < LICZ_ITER; i++)  // Skok w chwili 1
            pobudzenie[i] = 1.0;

        // Symulacja dzia³ania PID
        for (size_t i = 0; i < LICZ_ITER; i++) {
            faktyczne[i] = pid.simulate(pobudzenie[i]);
        }

        //do policzenia
        spodziewane = {0.0,3.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,21.0};

        // Porównanie wyników
        if (porownajSekwencje(spodziewane, faktyczne)) {
            std::cerr << "OK!\n";
        }
        else {
            std::cerr << "FAIL!\n";
            raportBledu(spodziewane, faktyczne);
        }
    }
    catch (...) {
        std::cerr << "Niespodziewany wyj¹tek!\n";
    }

}
int main()
{
    TestPID::test_PID_skokJednostkowy();
    return 0;

}