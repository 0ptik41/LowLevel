#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


int main(int argc, char *argv[]){
	int port;
	if(argc < 3){
		printf("Usage: %s <rhost> <rport>\n");
		return 1;
	}else{
		port = atoi(argv[2]);
	}

	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;

	serverAddr.sin_family = AF_INET;
  	serverAddr.sin_port = htons(port);
  	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  	addr_size = sizeof serverAddr;
  	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  	recv(clientSocket, buffer, 1024, 0);
  	printf("Data received: %s",buffer);  	
	return 0;
}

  

  
   

