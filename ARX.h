#pragma once
#include <vector>
#include <deque>
#include <random>

class model_ARX {
private:
    std::vector<double> values_A;          // współczynniki A
    std::vector<double> values_B;          // współczynniki B
    int delay;                             // opóźnienie
    double y_output = 0.0;                 // ostatnie wyjście
    double disruption_amplitude = 0.0;
    std::deque<double> buffer_input;       // bufor wejść (u)
    std::deque<double> buffer_output_y;    // bufor poprzednich wyjść (y)
    std::mt19937 rng;
    std::random_device seed_rng;
    bool Zresetowany=false;

public:
    // Konstruktor: inicjalizuje bufory zerami
    model_ARX(const std::vector<double>& A,
              const std::vector<double>& B,
              int delay_,
              double disruption_amp);

    model_ARX() = delete;
    model_ARX(const model_ARX& o) = default;
    model_ARX& operator=(const model_ARX& o) = default;
    ~model_ARX() = default;

    // reset: czyści stany wewnętrzne
    void reset();

    // Główna funkcja symulacji modelu ARX
    double Simulate(double u);
    void set_vector_A(const std::vector<double>& A);
    void set_vector_B(const std::vector<double>& B);
    void setZresetowany(bool z){Zresetowany=z;}
    bool getZresetowany(){return Zresetowany;}
    void set_latency(int d);
    void set_disruption_amplitude(double amp);
    void set_Wszystko(const std::vector<double>& A,
                      const std::vector<double>& B,
                      int delay_,
                      double disruption_amp);
};
