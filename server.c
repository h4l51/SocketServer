#include "server.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int openSocket(struct sockaddr_in address, ){
    int server_fd, new_socket;
    int opt = 1;
    int addrlen = sizeof(address);

    //Socket filedescriptor erstellen
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("Socket creation failed...");
        exit(1);
    }
    //Socket an Port binden
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("Bind fehlgeschlagen");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("Listen fehlgeschlagen");
        exit(EXIT_FAILURE);
    }
    //Neue Connections annehmen
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0)
    {
        perror("Connection fehlgeschlagen...");
        exit(EXIT_FAILURE);
    }
}


int main() {
    int value;

    char path[PATH_MAX];
    char *out;

    char buffer[1024] = {0};
    char *answer = "Message sent to Server.";
    char *print = "Server erfolgreich verbunden!";
    struct sockaddr_in address;




    int new_socket = openSocket(address);


    value = read( new_socket , buffer, 1024);
    printf("Received Value: %s", buffer);

    send(new_socket, answer, strlen(answer), 0);
    //Ignore sigpipe
    signal(SIGPIPE, SIG_IGN);




    return 0;
}


