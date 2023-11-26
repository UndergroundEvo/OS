#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void kot(int);
extern char name[];

int main(){
	pid_t p = getpid();
	ps(p);

	fprintf(stdout,"%s",name);
}
