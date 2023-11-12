#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

const int bufferSize = 5;  // Размер буфера

std::queue<int> buffer;  // Очередь буфера
std::mutex mtx;  // Мьютекс для обеспечения безопасности доступа к буферу
std::condition_variable producerCV, consumerCV;  // Условные переменные для синхронизации производителя и потребителя

void producer() {
    for (int i = 0; ; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        producerCV.wait(lock, []() { return buffer.size() < bufferSize; });  // Ждем, пока буфер не станет меньше максимального размера
        buffer.push(i);
        std::cout << "Производитель произвел: " << i << std::endl;
        lock.unlock();
        consumerCV.notify_one();  // Уведомляем потребителя
    }
}

void consumer() {
    for (;;) {
        std::unique_lock<std::mutex> lock(mtx);
        consumerCV.wait(lock, []() { return !buffer.empty(); });  // Ждем, пока буфер не станет непустым
        int data = buffer.front();
        buffer.pop();
        std::cout << "Потребитель потребил: " << data << std::endl;
        lock.unlock();
        producerCV.notify_one();  // Уведомляем производителя
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
