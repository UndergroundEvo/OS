#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
	pid_t son = (int) getpid();
	pid_t key;
	char cat[] = " (^・ω・^ )____";

	//pid_t son = fork();
	
	printf("%s %d \n", "Myau! my name is",son);
	printf("%s \n", cat);
	getchar();
	char sonC[6], com[] = "ps -e -o pid,ppid,pgid,sid,state,command | grep ";
	//snprintf(com,sizeof(com), "%d", son);
	sprintf(sonC, "%d", son);
	strcat(com, sonC);
	printf("%s \n", com);

	system(com);
	printf("%s \n", "Cat can kill some procces");
	printf("%s \n", "Enter PID to kill / enter 0 to close");
	scanf("%d", &key);
	if (key == 0) return 0;
	kill(key, SIGTERM);
	return 0;
}