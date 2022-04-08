#include "server.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int openSocket(){
    int server_fd, new_socket;
    struct sockaddr_in address;
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

    return new_socket;
}

int readSocket(int socket){
    char buffer[PATH_MAX];
    int value;
    value = read(socket, buffer, PATH_MAX);
    if (value < 0){
        perror("Error reading...");
        return -2;
    }
    else if (value == 0){
        //EOF
        return -1;
    }
    else{
        fprintf(stderr, "Received value: %s ", buffer);
    }

}

int main() {
    int compare;
    char *answer = "Done";
    int new_socket;
    new_socket = openSocket();

    while(1) {

        readSocket(new_socket);

        //Ignore sigpipe
        signal(SIGPIPE, SIG_IGN);

    }
    return 0;
}