#include <stdio.h>
#include <stdlib.h>
#include "config.h"

void read_server_config(int *port) {
    FILE *config_file = fopen("../config/server_config.txt", "r");
    if (config_file == NULL) {
        perror("Unable to open config file, using default settings.");
        return;
    }
    fscanf(config_file, "%d", port);
    fclose(config_file);
}
