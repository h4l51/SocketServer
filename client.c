//
// Created by Felix Halstrup on 06.04.22.
//

#include "client.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int connectToServer(int sock, struct sockaddr_in server_addr, char* address){


    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error creating socket...");
        exit(1);
    }

    if(inet_pton(AF_INET, address, &server_addr.sin_addr)<=0)
    {
        perror("Invalid address...");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection failed...");
        exit(1);
    }

    return sock;

}

int main(int argc, char const *argv[]){

    if(argc <= 1){
        perror("No arguments provided");
        exit(1);
    }
    int sock = 0;
    struct sockaddr_in server_addr;
    char* message = argv[2];
    char* address = argv[1];
    char buffer[1024] = {0};

    //Socket zum Verbinden

    sock = connectToServer(sock, server_addr, address);

    send(sock, message, strlen(message), 0);

    int value = read(sock, buffer, 1024);

    printf("%s", buffer);

    return 0;

}
