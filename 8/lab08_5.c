#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h> 


int main() {
    clock_t start = clock();

    long double pi = 0;
    int j = 1;
    const int prec = 64;
    for (int i = 1; i < 500000000; i++) {
        pi += (double)4 / j;
        j += 2;
        pi -= (double)4 / j;
        j += 2;
    }

    printf("w = %2d p = %2d pi = %*.*Lf\n", 62, 62, 62, 62, pi);
    clock_t end = clock();
    printf("%s%f%s\n","Потрачено на вычисление и вывод: ",(double)(end - start) / CLOCKS_PER_SEC, " сек.");
    return 0;
}