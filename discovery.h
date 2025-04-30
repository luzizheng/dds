/*
 * @Author: LuZizheng lu.zizheng@byd.com
 * @Date: 2025-04-30 09:12:28
 * @LastEditors: LuZizheng lu.zizheng@byd.com
 * @LastEditTime: 2025-04-30 11:24:04
 * @FilePath: /Dinix/bydos/lib/dds/discovery.h
 * @Description: 
 * 
 * Copyright (c) 2025 by BYD, All Rights Reserved. 
 */
#ifndef DDS_DISCOVERY_H
#define DDS_DISCOVERY_H

// Discovery interface
typedef struct {
    void (*register_endpoint)(const char *topic, int is_publisher);
    void (*lookup_endpoint)(const char *topic);
} Discovery_Interface;

// Global Discovery Service Interface
extern Discovery_Interface discovery_service;

void discovery_register_endpoint(const char *topic, int is_publisher);
void discovery_lookup_endpoint(const char *topic);

// Register a participant with the discovery service
int discovery_register_participant(DDS_Participant *participant);
// Register a publisher with the discovery service
int discovery_register_publisher(DDS_Participant *participant, const char *topic);
// Register a subscriber with the discovery service
int discovery_register_subscriber(DDS_Participant *participant, const char *topic);

#endif // DISCOVERY_H
