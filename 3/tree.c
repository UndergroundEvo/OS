#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int level = 1;
char const offsets[] = "\t\t\t\t\t\t\t\t";

pid_t create_child_process(int(*child_fn)()) {
	// Flush the output buffers to avoid duplicate output from the child process.
	fflush(stdout);
	fflush(stderr);

	pid_t child_pid = fork();
	switch(child_pid) {
		case 0: // Child process.
			++level;
			exit(child_fn());
		case -1: // fork() failed.
			abort();
		default: // Parent process.
			printf("%.*s %u spawned %u\n", level, offsets, (unsigned)getpid(), (unsigned)child_pid);
			return child_pid;
	}
}

void wait_for_any_child() {
	int wstatus;
	pid_t child_pid = wait(&wstatus);
	if(child_pid == -1)
		abort();
	printf("%.*s %u terminated\n", level, offsets, (unsigned)child_pid);
}

int p2() { return 0; }
int p5() { return 0; }
int p6() { return 0; }
int p7() { return 0; }

int p4() {
	create_child_process(p5);
	create_child_process(p6);
	create_child_process(p7);
	getchar();
	wait_for_any_child();
	wait_for_any_child();
	wait_for_any_child();
	return 0;
}
int p3() {
	create_child_process(p4);
	wait_for_any_child();
	return 0;
}

int p1() {
	printf("%u started\n", (unsigned)getpid());
	create_child_process(p2);
	create_child_process(p3);
	wait_for_any_child();
	wait_for_any_child();
	printf("%u terminated\n", (unsigned)getpid());
	return 0;
}

int main() {
	p1();
	getchar();
}
