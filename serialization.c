#include "serialization.h"
#include <string.h>


int serialize_payload(const void *data, size_t size, void *buffer, size_t buffer_size) {
    if (size > buffer_size) {
        return -1; // Not enough space
    }
    memcpy(buffer, data, size);
    return size; // Return the number of bytes serialized
}

int deserialize_payload(const void *buffer, size_t buffer_size, void *data, size_t data_size) {
    if (buffer_size > data_size) {
        return -1; // Not enough space in the data buffer
    }
    memcpy(data, buffer, buffer_size);
    return buffer_size; // Return the number of bytes deserialized
}