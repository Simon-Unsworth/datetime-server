#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define ERROR -1
#define BACKLOG 32

int main(int argc, char *argv[]) {
    // attempt to setup an endpoint for communication
    int servfd = socket(AF_INET, SOCK_STREAM, 0);

    // attempt failed print error and exit gracefully
    if(servfd == ERROR) {
        perror("Socket Error");
        exit(EXIT_FAILURE);
    }

    // setup the servers address structure
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(5555),
        .sin_addr.s_addr = INADDR_ANY
    };

    // attempt to bind the socket to the designated port
    if(bind(servfd, (struct sockaddr *) &address, sizeof(address)) == ERROR) {
        // attempt failed print error and exit gracefully
        perror("Bind Error");
        exit(EXIT_FAILURE);
    }

    // attempt to put the server into a passive listening state
    if(listen(servfd, BACKLOG) == ERROR) {
        // attempt failed print error and exit gracefully
        perror("Listen Error");
        exit(EXIT_FAILURE);
    }

    socklen_t length = sizeof(address);
    int clientfd = accept(servfd, (struct sockaddr *) &address, &length);

    if(clientfd == ERROR) {
        perror("Accept Error");
        exit(EXIT_FAILURE);
    }

    // get the current date/time as a string
    time_t current_time;
    time(&current_time);
    const char *str_time = ctime(&current_time);

    send(clientfd, str_time, strlen(str_time), 0);

    return 0;
}
