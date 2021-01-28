#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[]){
    int port;
    // check args
    if (argc < 2){
        printf("Usage: %s <lport>\n", argv[0]);
        return 0;
    }else{
        port = atoi(argv[1]);
    }

    // setup server socket 
    int serveSock;
    char srvBuff[1024];
    struct sockaddr_in serverAddress;
    struct sockaddr_storage serveStorage;
    socklen_t addr_size;

    serveSock = socket(PF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr("0.0.0.0");
    memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);

    // Start Listening for connections (5 allowed)
    bind(serveSock, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if (listen(serveSock, 5) == 0)
        printf("[*] Listening\n");
    else
        printf("[!] Unable to start listening\n");

    // Accept Clients 
    addr_size = sizeof serveStorage;
    int client_sock = accept(serveSock, (struct  sockaddr *) &serveStorage, &addr_size);
    // do something with client 
    strcpy(srvBuff, "~ Connected to Server ~\n");
    send(client_sock, srvBuff, 25, 0);
    
    bool connected = true;

    memset(srvBuff, '\0', sizeof(srvBuff));
    recv(client_sock, srvBuff, sizeof(srvBuff), 0);
    printf("> %s", srvBuff);
    
    return 0;
}