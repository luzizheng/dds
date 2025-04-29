#ifndef DISCOVERY_H
#define DISCOVERY_H

// Discovery interface
typedef struct {
    void (*register_endpoint)(const char *topic, int is_publisher);
    void (*lookup_endpoint)(const char *topic);
} Discovery_Interface;

// Global Discovery Service Interface
extern Discovery_Interface discovery_service;

#endif // DISCOVERY_H