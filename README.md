# UDP Time Server and Client
A C-based UDP time server and client application. The server responds to time requests from multiple clients, providing the current date and time. Includes features for server configuration and request logging, ideal for learning network programming and client-server architecture.

## Overview
This project implements a simple UDP-based time server and client in C. The server responds to time requests from clients by sending back the current date and time. The client can request the time from a specified server IP address.

## Features
- Server can handle multiple client requests.
- Logs client requests to a file (`server_log.txt`).
- Server configuration through a configuration file (`server_config.txt`).
- Command-line arguments for client to specify server IP.

## Requirements
- C compiler (e.g., `gcc`)
- `libpcap` library for packet capture

## Build
To build the project, run the following command from the `src/` directory:

```bash
make
