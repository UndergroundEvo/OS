#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
const int buffer_size = 5;  // Размер буфера

queue<int> buffer;  // Очередь для буфера
mutex mtx;          // Мьютекс для синхронизации доступа к буферу
condition_variable buffer_empty;  // Условная переменная для оповещения о пустом буфере
condition_variable buffer_full;   // Условная переменная для оповещения о полном буфере

// Функция производителя
void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx);

        // Проверка, если буфер полон, ждем, пока не появится место
        buffer_full.wait(lock, [] { return buffer.size() < buffer_size; });

        // Генерация элемента
        int item = rand() % 100;
        cout << "Изготовитель №" << id << " придумал число: " << item << endl;

        // Добавление элемента в буфер
        buffer.push(item);

        // Оповещаем потребителя о наличии нового элемента
        buffer_empty.notify_all();
    }
}

// Функция потребителя
void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx);

        // Проверка, если буфер пуст, ждем, пока не появится элемент
        buffer_empty.wait(lock, [] { return !buffer.empty(); });

        // Извлечение элемента из буфера
        int item = buffer.front();
        buffer.pop();
        cout << "Потребитель №" << id << " получил число: " << item << endl;

        // Оповещаем производителя о наличии места в буфере
        buffer_full.notify_all();
    }
}

int main() {
    // Создание потоков производителей и потребителей
    thread producer1(producer, 1);
    thread producer2(producer, 2);
    thread consumer1(consumer, 1);
    thread consumer2(consumer, 2);

    // Ожидание завершения потоков
    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();

    return 0;
}
