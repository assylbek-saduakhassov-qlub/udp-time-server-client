#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "config.h"

#define DEFAULT_PORT 9000
#define BUFFER_SIZE 1024

// Function to log server activities
void log_activity(const char *message) {
    FILE *log_file = fopen("server_log.txt", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }
    fprintf(log_file, "%s\n", message);
    fclose(log_file);
}

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_address, client_address;
    socklen_t len = sizeof(client_address);
    int port = DEFAULT_PORT;

    // Read server configuration
    read_server_config(&port);

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
    memset(&client_address, 0, sizeof(client_address));

    // server information
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    // bind the socket to the specified IP and port
    if (bind(sockfd, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Time server started on port %d:\n", port);
    log_activity("Server started");

    // infinite loop to handle incoming messages (from clients)
    while (1) {
        int n;

        // receive message from client
        n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_address, &len);
        buffer[n] = '\0';

        // get client IP and port
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_address.sin_port);

        // log and print message indicating receipt
        char log_message[BUFFER_SIZE];
        snprintf(log_message, sizeof(log_message), "Time request from: %s:%d", client_ip, client_port);
        log_activity(log_message);
        printf("%s\n", log_message);

        // get current system time and date
        time_t now = time(NULL);
        char time_str[BUFFER_SIZE];
        strftime(time_str, sizeof(time_str), "%c", localtime(&now));

        // send current time and date back to the client
        sendto(sockfd, time_str, strlen(time_str), 0, (struct sockaddr *)&client_address, len);
    }

    // close the socket (unreachable code in this example because of the infinite loop)
    close(sockfd);
    return 0;
}
