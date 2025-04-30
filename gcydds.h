/*
 * @Author: LuZizheng lu.zizheng@byd.com
 * @Date: 2025-04-30 09:16:24
 * @LastEditors: LuZizheng lu.zizheng@byd.com
 * @LastEditTime: 2025-04-30 10:16:43
 * @FilePath: /Dinix/bydos/lib/dds/gcydds.h
 * @Description: 
 * 
 * Copyright (c) 2025 by BYD, All Rights Reserved. 
 */
#ifndef GCY_DDS_H
#define GCY_DDS_H

#include <stddef.h>
#include <stdint.h>

// Domain ID max
#define DDS_MAX_DOMAIN_ID 32
#define DDS_ENDPOINT "gcydds"
// Participant structure
typedef struct {
    uint8_t domain_id;   // Domain ID for segregation
} DDS_Participant;

// Publisher structure
typedef struct {
    DDS_Participant *participant;
    char topic[64];
} DDS_Publisher;

// Subscriber structure
typedef struct {
    DDS_Participant *participant;
    char topic[64];
    void (*on_data_received)(const void *data, size_t size);
} DDS_Subscriber;

// Function prototypes
DDS_Participant *dds_create_participant(uint8_t domain_id);
DDS_Publisher *dds_create_publisher(DDS_Participant *participant, const char *topic);
DDS_Subscriber *dds_create_subscriber(DDS_Participant *participant, const char *topic, 
                                       void (*on_data_received)(const void *data, size_t size));

int dds_publish(DDS_Publisher *publisher, const void *data, size_t size);
int dds_subscribe(DDS_Subscriber *subscriber);
int dds_remove_participant(DDS_Participant *participant);
int dds_remove_publisher(DDS_Publisher *publisher);
int dds_remove_subscriber(DDS_Subscriber *subscriber);

#endif // DDS_H
