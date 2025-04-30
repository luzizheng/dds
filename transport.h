/*
 * @Author: LuZizheng lu.zizheng@byd.com
 * @Date: 2025-04-30 09:16:43
 * @LastEditors: LuZizheng lu.zizheng@byd.com
 * @LastEditTime: 2025-04-30 09:21:47
 * @FilePath: /Dinix/bydos/lib/dds/transport.h
 * @Description: 
 * 
 * Copyright (c) 2025 by BYD, All Rights Reserved. 
 */
#ifndef DDS_TRANSPORT_H
#define DDS_TRANSPORT_H

#include <stdint.h>
#include <stddef.h>

// Transport Interface
typedef struct {
    int (*send)(const char *address, uint16_t port, const void *data, size_t size);
    int (*receive)(void *buffer, size_t buffer_size);
} Transport_Interface;

// Global Transport Interface
extern Transport_Interface transport_tcp;

#endif // TRANSPORT_H