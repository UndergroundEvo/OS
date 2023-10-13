#include<stdio.h>

void kot(int);
extern char name[];

int main(){
	kot(5);
	fprintf(stdout,"%s",name);
}
