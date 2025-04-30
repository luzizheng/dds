/*
 * @Author: LuZizheng lu.zizheng@byd.com
 * @Date: 2025-04-30 09:12:21
 * @LastEditors: LuZizheng lu.zizheng@byd.com
 * @LastEditTime: 2025-04-30 10:10:53
 * @FilePath: /Dinix/bydos/lib/dds/discovery.c
 * @Description: 
 * 
 * Copyright (c) 2025 by BYD, All Rights Reserved. 
 */
#include "discovery.h"
#include <stdio.h>
#include <string.h>
#include <dinix/ipc.h>
#include <stdlib.h>
#include "ddscrc16.h" // Assume a CRC16 library is available
#include <unistd.h>
#include <dinix/com.h>
#include "gcydds.h"

#define FRAME_SIZE 64
#define CRC16_TRAILER_SIZE 2

#ifndef ANY
#define ANY ((endpoint_t) - 1)
#endif

// Helper function: Compute CRC16
static uint16_t compute_crc16(const void *data, size_t size) {
    return dds_crc16(0, data, size);
}


// Register an endpoint
void discovery_register_endpoint(const char *topic, int is_publisher) {
    char frame[FRAME_SIZE];
    memset(frame, 0, FRAME_SIZE);

    // Copy topic and type (publisher or subscriber) into the frame
    snprintf(frame, FRAME_SIZE - CRC16_TRAILER_SIZE, "%s|%s",
             topic, is_publisher ? "pub" : "sub");

    // Compute CRC16 trailer
    uint16_t crc = compute_crc16(frame, FRAME_SIZE - CRC16_TRAILER_SIZE);
    memcpy(frame + FRAME_SIZE - CRC16_TRAILER_SIZE, &crc, CRC16_TRAILER_SIZE);

    // Send frame via Minix IPC (e.g., to the discovery service)
    message m;
    m.m1_p1 = frame;
    m.m1_i1 = FRAME_SIZE;
    if (ipc_send(getpid(), &m) != 0) {
        fprintf(stderr, "Failed to register endpoint\n");
    }
}



// Lookup an endpoint
void discovery_lookup_endpoint(const char *topic) {
    message m;
    m.m1_p1 = (char *)topic;
    m.m1_i1 = strlen(topic) + 1;

    // Send lookup request via Minix IPC
    if (ipc_send(getpid(), &m) != 0) {
        fprintf(stderr, "Failed to lookup endpoint\n");
        return;
    }

    // Receive response (for simplicity, assume response is a single message)
    int st;
    if (ipc_receive(ANY, &m, &st) != 0) {
        fprintf(stderr, "Failed to receive endpoint data\n");
        return;
    }

    printf("Endpoint data: %s\n", m.m1_p1);
}

// Discovery service interface
Discovery_Interface discovery_service = {
    .register_endpoint = discovery_register_endpoint,
    .lookup_endpoint = discovery_lookup_endpoint
};