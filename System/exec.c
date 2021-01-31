#include <stdlib.h>
#include <stdio.h>

// most basic access to "shell" I can make
int shell(){
	char commandBuff[1028];
	printf("$ ");
	scanf("%s", commandBuff);
	return system(commandBuff);
}

int main(int argc, char *argv[]){
	// run commands one by one
	while(1){
		shell();
	}	
}