#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <atomic>
#include <ctime>
using namespace std;

const int num_threads = 4; // Количество потоков для параллельных вычислений
const int iterations_per_thread = 125000000; // Количество итераций на каждом потоке

atomic<double> pi{ 0.0 }; // Используем атомарную переменную для суммирования

void calculatePi(int start, int end) {
    double localSum = 0;
    int j = 2 * start + 1;

    for (int i = start; i < end; i++){
        if (i % 2 == 0) {
            localSum += 4.0 / j;
        }
        else {
            localSum -= 4.0 / j;
        }
        j += 2;
    }
    pi.store(localSum, memory_order_relaxed);
}

int main() {
    clock_t start_time = clock();
    vector<thread> threads;
    for (int i = 0; i < num_threads; i++) {
        int start = i * iterations_per_thread;
        int end = start + iterations_per_thread;
        threads.push_back(thread(calculatePi, start, end));
    }

    for (auto& t : threads) t.join();

    cout << setprecision(64) << pi << endl;
    clock_t end_time = clock();
    cout << "Потрачено на вычисление и вывод: " << setprecision(3) << (double)(end_time - start_time) / CLOCKS_PER_SEC << " сек." << endl;
    return 0;
}