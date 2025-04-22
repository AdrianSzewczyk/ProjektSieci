/*#pragma once
#include <vector>
#include <queue>
#include <numeric>
#include <iostream>
#include <random>
#include "Wybor.h"
class model_ARX 
{
private:
	int iteration = 0;
	double y_output = 0;
	int input_buffer_size = 1;
    double disruption_amplitude = 0.0;
	std::vector<double> values_A;
	std::vector<double> values_B;
	std::deque<double> buffer_input;
	std::deque<double> buffer_error_u;
	std::deque<double> buffer_output_y;
	std::random_device seed_rng;
	std::mt19937 rng;
public:
	void Iterate();
	double Simulate(double pid_val);
    /*model_ARX(std::vector<double> A, std::vector<double> B, int inp, double disruption_amp)
	{
		values_A = A;
		values_B = B;
		if (inp < 1) inp = 1;
		input_buffer_size = inp;
        //buffer_input.resize(input_buffer_size);
        //buffer_error_u.resize(values_B.size());
        //buffer_output_y.resize(values_A.size());
        disruption_amplitude = disruption_amp;
		rng.seed(seed_rng());
    }*//*
    model_ARX(std::vector<double> A_, std::vector<double> B_, int inp, double disruption_amp)
        : values_A(std::move(A_))
        , values_B(std::move(B_))
        , input_buffer_size(std::max(1, inp))
        , disruption_amplitude(disruption_amp)
    {
        // 1) Bufor wejść – trzyma ostatnie pid_val (rozmiar = opóźnienie)
        buffer_input.assign(input_buffer_size, 0.0);
        // 2) Bufor opóźnień dla B (wejść do sumy B)
        buffer_error_u.assign(values_B.size(), 0.0);
        // 3) Bufor poprzednich wyjść dla A
        buffer_output_y.assign(values_A.size(), 0.0);

        rng.seed(seed_rng());
    }

	model_ARX() = delete;
    model_ARX& operator=(const model_ARX& o);
    model_ARX(const model_ARX& o);
	void set_vector_A(std::vector<double> A);
	void set_vector_B(std::vector<double> B);
	void set_latency(int inp);
    void set_disruption_amplitude(double amp);
    void reset();
	std::vector<double> get_vector_A();
	std::vector<double> get_vector_B();
	int get_latency();
    double getYoutput(){return y_output;}
    double get_disruption_amplitude() const;
	~model_ARX() {};
};*/
// ARX.h
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

public:
    // Konstruktor: inicjalizuje bufory zerami
    model_ARX(const std::vector<double>& A,
              const std::vector<double>& B,
              int delay_,
              double disruption_amp)
        : values_A(A)
        , values_B(B)
        , delay(std::max(1, delay_))
        , disruption_amplitude(disruption_amp)
    {
        buffer_input.assign(values_B.size() + delay, 0.0);
        buffer_output_y.assign(values_A.size(), 0.0);
        rng.seed(seed_rng());
    }

    model_ARX() = delete;
    model_ARX(const model_ARX& o) = default;
    model_ARX& operator=(const model_ARX& o) = default;
    ~model_ARX() = default;

    // reset: czyści stany wewnętrzne
    void reset() {
        buffer_input.assign(values_B.size() + delay, 0.0);
        buffer_output_y.assign(values_A.size(), 0.0);
        y_output = 0.0;
    }

    // Główna funkcja symulacji modelu ARX
    double Simulate(double u) {
        // 1) Dodaj nowe wejście
        buffer_input.push_front(u);
        if (buffer_input.size() > values_B.size() + delay)
            buffer_input.pop_back();

        // 2) Wstaw ostatnie wyjście do bufora
        buffer_output_y.push_front(y_output);
        if (buffer_output_y.size() > values_A.size())
            buffer_output_y.pop_back();

        // 3) Początkowy transjent: jeszcze za mało próbek
        if (buffer_input.size() < values_B.size() + delay ||
            buffer_output_y.size() < values_A.size()) {
            return y_output;
        }

        // 4) Oblicz sumy: B * u[k-delay-i]
        double sum_B = 0.0;
        for (size_t i = 0; i < values_B.size(); ++i) {
            sum_B += values_B[i] * buffer_input[delay + i];
        }

        // 5) Oblicz sumy: A * y[k-1-i]
        double sum_A = 0.0;
        for (size_t i = 0; i < values_A.size(); ++i) {
            sum_A += values_A[i] * buffer_output_y[i];
        }

        // 6) Zakłócenia (opcjonalne)
        double dis = 0.0;
        if (disruption_amplitude > 0.0) {
            std::normal_distribution<double> dist(0.0, disruption_amplitude);
            dis = dist(rng);
        }

        // 7) Nowe wyjście
        y_output = sum_B - sum_A + dis;
        return y_output;
    }

    // Gettery i settery w razie potrzeby...
    void set_vector_A(const std::vector<double>& A) {
        values_A = A;
        buffer_output_y.assign(values_A.size(), 0.0);
    }
    void set_vector_B(const std::vector<double>& B) {
        values_B = B;
        buffer_input.assign(values_B.size() + delay, 0.0);
    }
    void set_latency(int d) {
        delay = std::max(1, d);
        buffer_input.assign(values_B.size() + delay, 0.0);
    }
    void set_disruption_amplitude(double amp) {
        disruption_amplitude = amp;
    }
};
