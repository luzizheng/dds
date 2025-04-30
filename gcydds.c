#include "gcydds.h"
#include "discovery.h"
#include "domain_router.h"
#include "serialization.h"
#include "transport.h"
#include <stdlib.h>
#include <string.h>

// Create a participant
DDS_Participant *dds_create_participant(uint8_t domain_id) {
    if (domain_id > DDS_MAX_DOMAIN_ID) {
        return NULL; // Invalid domain ID
    }

    DDS_Participant *participant = (DDS_Participant *)malloc(sizeof(DDS_Participant));
    if (!participant) {
        return NULL; // Memory allocation failed
    }

    participant->domain_id = domain_id;

    // Register the participant with the discovery daemon
    if (discovery_register_participant(participant) != 0) {
        free(participant);
        return NULL;
    }

    return participant;
}

// Create a publisher
DDS_Publisher *dds_create_publisher(DDS_Participant *participant, const char *topic) {
    if (!participant || !topic) {
        return NULL; // Invalid arguments
    }

    DDS_Publisher *publisher = (DDS_Publisher *)malloc(sizeof(DDS_Publisher));
    if (!publisher) {
        return NULL; // Memory allocation failed
    }

    publisher->participant = participant;
    strncpy(publisher->topic, topic, sizeof(publisher->topic) - 1);
    publisher->topic[sizeof(publisher->topic) - 1] = '\0'; // Ensure null-termination

    // Register the publisher with the discovery daemon
    if (discovery_register_publisher(participant, topic) != 0) {
        free(publisher);
        return NULL;
    }

    return publisher;
}

// Create a subscriber
DDS_Subscriber *dds_create_subscriber(DDS_Participant *participant, const char *topic,
                                      void (*on_data_received)(const void *data, size_t size)) {
    if (!participant || !topic || !on_data_received) {
        return NULL; // Invalid arguments
    }

    DDS_Subscriber *subscriber = (DDS_Subscriber *)malloc(sizeof(DDS_Subscriber));
    if (!subscriber) {
        return NULL; // Memory allocation failed
    }

    subscriber->participant = participant;
    strncpy(subscriber->topic, topic, sizeof(subscriber->topic) - 1);
    subscriber->topic[sizeof(subscriber->topic) - 1] = '\0'; // Ensure null-termination
    subscriber->on_data_received = on_data_received;

    // Register the subscriber with the discovery daemon
    if (discovery_register_subscriber(participant, topic) != 0) {
        free(subscriber);
        return NULL;
    }

    return subscriber;
}

// Publish data
int dds_publish(DDS_Publisher *publisher, const void *data, size_t size) {
    if (!publisher || !data || size == 0) {
        return -1; // Invalid arguments
    }

    // Serialize the data
    void *serialized_data = serialization_encode(data, size);
    if (!serialized_data) {
        return -1; // Serialization failed
    }

    // Send the data via the transport layer
    int result = transport_send(publisher->participant->domain_id, publisher->topic, serialized_data, size);

    // Clean up
    free(serialized_data);
    return result;
}

// Subscribe to data
int dds_subscribe(DDS_Subscriber *subscriber) {
    if (!subscriber) {
        return -1; // Invalid arguments
    }

    // Use the transport layer to listen for messages
    return transport_receive(subscriber->participant->domain_id, subscriber->topic, subscriber->on_data_received);
}

// Remove a participant
int dds_remove_participant(DDS_Participant *participant) {
    if (!participant) {
        return -1; // Invalid argument
    }

    // Deregister the participant from the discovery daemon
    if (discovery_deregister_participant(participant) != 0) {
        return -1; // Deregistration failed
    }

    // Free the participant memory
    free(participant);
    return 0;
}

// Remove a publisher
int dds_remove_publisher(DDS_Publisher *publisher) {
    if (!publisher) {
        return -1; // Invalid argument
    }

    // Deregister the publisher from the discovery daemon
    if (discovery_deregister_publisher(publisher->participant, publisher->topic) != 0) {
        return -1; // Deregistration failed
    }

    // Free the publisher memory
    free(publisher);
    return 0;
}

// Remove a subscriber
int dds_remove_subscriber(DDS_Subscriber *subscriber) {
    if (!subscriber) {
        return -1; // Invalid argument
    }

    // Deregister the subscriber from the discovery daemon
    if (discovery_deregister_subscriber(subscriber->participant, subscriber->topic) != 0) {
        return -1; // Deregistration failed
    }

    // Free the subscriber memory
    free(subscriber);
    return 0;
}







