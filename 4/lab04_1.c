#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child1, child2;
    child1 = fork();  // Создаем первый дочерний процесс
    
    if (child1 < 0){
        perror("Ошибка fork()");
        exit(1);
    }
    if (child1 == 0){// Запуск ls в первом fork()
        printf("Дочерний процесс 1 (PID: %d)\n", getpid());
        execlp("/bin/ls", "ls", NULL);
        perror("Ошибка execlp()");
        exit(1);
    } 
    else{
        child2 = fork();// Создаем второй дочерний процесс
        if (child2 < 0){
            perror("Ошибка fork()");
            exit(1);
        }
        
        if (child2 == 0) {//запуск ps в втором дочернем процессе
            printf("Дочерний процесс 2 (PID: %d)\n", getpid());
            execlp("/bin/ps", "ps", NULL);
            perror("Ошибка execlp()");
            exit(1);
        } else {
            printf("Родительский процесс (PID: %d)\n", getpid());
            getchar();
            wait(NULL);
            wait(NULL);
            printf("Оба дочерних процесса завершились.\n");
        }
    }
    
    return 0;
}