#ifndef TRANSPORT_H
#define TRANSPORT_H

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