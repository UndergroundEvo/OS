#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <cmath>
#include <mutex>
#include <ctime>
using namespace std;
std::mutex mutex;
long double result = 0.0;

void calculatePi(int start, int end, double step) {
    long double sum = 0.0;
    for (int i = start; i < end; ++i) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    lock_guard<std::mutex> lock(std::mutex);
    result += sum;
}

int main() {
    const int num_threads = 1; // Установите желаемое количество потоков
    const int num_steps = 100000000; // Установите желаемое количество шагов

    long double step = 1.0 / num_steps;

    vector<std::thread> threads;
    clock_t start_time = clock();
    for (int i = 0; i < num_threads; ++i) {
        int start = i * (num_steps / num_threads);
        int end = (i + 1) * (num_steps / num_threads);

        threads.emplace_back(calculatePi, start, end, step);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    long double pi = result * step;
    cout << "Реальное число pi:    3.14159265358979323846264338327950288419716939937510582097494459" << endl;
    cout << "Вычисленное число pi: " << setprecision(64) << pi << endl;
    
    clock_t end_time = clock();
    cout << "Потрачено на вычисление и вывод: " << setprecision(3) << (double)(end_time - start_time) / CLOCKS_PER_SEC << " сек." << endl;
    return 0;
}
