#ifndef DDS_H
#define DDS_H

#include <stdint.h>
#include <stddef.h>

// Domain ID max
#define MAX_DOMAIN_ID 255

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

#endif // DDS_H