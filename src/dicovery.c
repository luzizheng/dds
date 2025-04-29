#include "discovery.h"
#include <minix/ipc.h>

static void discovery_register_endpoint(const char *topic, int is_publisher) {
    // Register the topic with the discovery service
}

static void discovery_lookup_endpoint(const char *topic) {
    // Lookup endpoint for the provided topic
}

Discovery_Interface discovery_service = {
    .register_endpoint = discovery_register_endpoint,
    .lookup_endpoint = discovery_lookup_endpoint
};