#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 9000
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sockfd;
    char buffer[BUFFER_SIZE];
    char *message = "Time request";
    struct sockaddr_in server_address;
    socklen_t len = sizeof(server_address);

    // Check for user input IP address
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // set socket options
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt error");
        exit(EXIT_FAILURE);
    }

    // initialize server address structure
    memset(&server_address, 0, sizeof(server_address));

    // server information
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    // send "Time request" to the server
    sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *)&server_address, sizeof(server_address));

    // wait for server's reply
    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_address, &len);
    buffer[n] = '\0';

    // print the server time
    printf("Server time: %s\n", buffer);

    // close the socket
    close(sockfd);
    return 0;
}
