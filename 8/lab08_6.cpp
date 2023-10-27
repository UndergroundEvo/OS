#include <iostream>
#include <iomanip>
#include <time.h> 
using namespace std;

int main(){
    clock_t start = clock();

    long double pi = 0;
    int j = 1;
    const int prec = 64;
    for (int i = 1; i < 500000000; i++){
        pi += (double)4 / j;
        j += 2;
        pi -= (double)4 / j;
        j += 2;
    }

    cout << setprecision(prec) << pi << endl;
    clock_t end = clock();
    cout << "Потрачено на вычисление и вывод: " << setprecision(3) << (double)(end - start) / CLOCKS_PER_SEC << " сек." << endl;
    return 0;
}
