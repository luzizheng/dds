/*
 * @Author: LuZizheng lu.zizheng@byd.com
 * @Date: 2025-04-30 09:16:51
 * @LastEditors: LuZizheng lu.zizheng@byd.com
 * @LastEditTime: 2025-04-30 09:20:44
 * @FilePath: /Dinix/bydos/lib/dds/transport.c
 * @Description: 
 * 
 * Copyright (c) 2025 by BYD, All Rights Reserved. 
 */
#include "transport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>


// Define maximum payload size and header size
#define MAX_PAYLOAD_SIZE 1024
#define HEADER_SIZE 4

// Helper function to create a socket and connect
static int create_socket_and_connect(const char *address, uint16_t port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, address, &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Socket connection failed");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

// Function to send a TCP message
static int send_tcp_message(const char *address, uint16_t port, const void *data, size_t size) {
    if (size > MAX_PAYLOAD_SIZE) {
        fprintf(stderr, "Payload exceeds maximum allowed size\n");
        return -1;
    }

    int sockfd = create_socket_and_connect(address, port);
    if (sockfd < 0) {
        return -1; // Connection failed
    }

    // Prepare header (4 bytes for length prefix)
    uint32_t payload_length = htonl(size);
    if (write(sockfd, &payload_length, HEADER_SIZE) != HEADER_SIZE) {
        perror("Failed to send header");
        close(sockfd);
        return -1;
    }

    // Send payload
    if (write(sockfd, data, size) != size) {
        perror("Failed to send payload");
        close(sockfd);
        return -1;
    }

    close(sockfd);
    return 0; // Success
}

// Function to receive a TCP message
static int receive_tcp_message(void *buffer, size_t buffer_size) {
    int sockfd = -1; // Socket should be initialized elsewhere
    uint32_t payload_length;

    // Read header
    if (read(sockfd, &payload_length, HEADER_SIZE) != HEADER_SIZE) {
        perror("Failed to read header");
        return -1;
    }

    payload_length = ntohl(payload_length);
    if (payload_length > buffer_size) {
        fprintf(stderr, "Payload exceeds buffer size\n");
        return -1;
    }

    // Read payload
    if (read(sockfd, buffer, payload_length) != payload_length) {
        perror("Failed to read payload");
        return -1;
    }

    return payload_length; // Return the size of the received payload
}

// Transport interface
Transport_Interface transport_tcp = {
    .send = send_tcp_message,
    .receive = receive_tcp_message
};