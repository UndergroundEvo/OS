#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

char name[]="Sibsutis";

void ps(pid_t pid) {
	char pidc[5], com[] = "ps -e -o pid,ppid,pgid,sid,state,command | grep ";
	sprintf(pidc, "%d", pid);
	strcat(com, pidc);
	printf("%s \n", com);
	system(com);
}
