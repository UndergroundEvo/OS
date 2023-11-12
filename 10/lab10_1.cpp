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

atomic<int> turn{ 0 };
atomic<bool> flag[num_threads];

void calculatePi(int start, int end, int thread_id) {
    double localSum = 0;
    int j = 2 * start + 1;

    for (int i = start; i < end; i++) {
        if (i % 2 == 0) {
            localSum += 4.0 / j;
        }
        else {
            localSum -= 4.0 / j;
        }
        j += 2;
    }

    flag[thread_id].store(false, memory_order_relaxed);

    int otherThread = 1 - thread_id;
    turn.store(otherThread, memory_order_relaxed);

    while (flag[otherThread].load(memory_order_relaxed) && turn.load(memory_order_relaxed) == otherThread) {
        // Ждем, пока другой поток завершит свою критическую секцию
    }

    //pi.fetch_add(localSum, memory_order_relaxed);
    pi.store(localSum);
}

int main() {
    clock_t start_time = clock();
    vector<thread> threads;

    for (int i = 0; i < num_threads; i++) {
        flag[i].store(true, memory_order_relaxed);
        threads.push_back(thread(calculatePi, i * iterations_per_thread, (i + 1) * iterations_per_thread, i));
    }

    for (auto& t : threads) t.join();

    cout << setprecision(64) << pi << endl;
    clock_t end_time = clock();
    cout << "Потрачено на вычисление и вывод: " << setprecision(3) << (double)(end_time - start_time) / CLOCKS_PER_SEC << " сек." << endl;

    return 0;
}
