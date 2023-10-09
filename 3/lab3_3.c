#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t son;
    pid_t father1;
    //pid_t father2;

    father1 = (int)getpid();
    fprintf(stdout, "FATHER1: %i \n", (int)getpid());
    
    son = fork();
    fprintf(stdout, "SON: %i \n", (int)getpid());
    getchar();

}