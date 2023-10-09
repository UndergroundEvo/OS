#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//ps -e -o pid,ppid,pgid,sid,state,command | grep 228

int main() {
	int choice;
	pid_t prog;
	pid_t parent = (int)getpid();
	while (choice != 5){
		printf("%s %d %s", "PPID:", parent, "\nChoice programm to start: \n");
		printf("0. Select prog \n");
		printf("1. PS | grep PPID\n");
		printf("5. Exit \n");
		scanf("%d", &choice);
		switch (choice){
			case (0):
				prog1 = fork();
				printf("%s %d \n","prog1=", prog);
				printf("Enter programm name (like <vim>)\n");
				
				char* args[100] = "/bin/";

				execlp("/bin/ps", "ps", NULL);


				execvp(args[0], args);
				break;
			case (1):
				printf("%s %d \n", "prog1=", fork());
				//char* args[] = { "ps -a",NULL };
				//execvp("ps", "-a");
				//execlp("/bin/ps", "ps", NULL);
				break;
			default:
				break;
		}
	}
	getchar();
	return 0;
}
