#include "ARX.h"
model_ARX::model_ARX(const std::vector<double>& A,
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


// reset: czyści stany wewnętrzne
void model_ARX::reset() {
    buffer_input.assign(values_B.size() + delay, 0.0);
    buffer_output_y.assign(values_A.size(), 0.0);
    //iterarion=0;
    y_output = 0.0;
}


// Główna funkcja symulacji modelu ARX
double model_ARX::Simulate(double u) {
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
void model_ARX::set_vector_A(const std::vector<double>& A) {
    values_A = A;
    buffer_output_y.assign(values_A.size(), 0.0);
}
void model_ARX::set_vector_B(const std::vector<double>& B) {
    values_B = B;
    buffer_input.assign(values_B.size() + delay, 0.0);
}
void model_ARX::set_latency(int d) {
    delay = std::max(1, d);
    buffer_input.assign(values_B.size() + delay, 0.0);
}
void model_ARX::set_disruption_amplitude(double amp) {
    disruption_amplitude = amp;
}
void model_ARX::set_Wszystko(const std::vector<double>& A,
                             const std::vector<double>& B,
                             int delay_,
                             double disruption_amp){

    set_vector_A(A);
    set_vector_B(B);
        set_latency(delay_);
    set_disruption_amplitude(disruption_amp);
}
