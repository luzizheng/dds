/*
 * @Author: LuZizheng lu.zizheng@byd.com
 * @Date: 2025-04-30 09:17:06
 * @LastEditors: LuZizheng lu.zizheng@byd.com
 * @LastEditTime: 2025-04-30 09:21:40
 * @FilePath: /Dinix/bydos/lib/dds/serialization.h
 * @Description: 
 * 
 * Copyright (c) 2025 by BYD, All Rights Reserved. 
 */
#ifndef DDS_SERIALIZATION_H
#define DDS_SERIALIZATION_H

#include <stddef.h> // For size_t

#ifdef __cplusplus
extern "C" {
#endif

// Serializes an object into a byte array
// Parameters:
// - obj: Pointer to the object to serialize
// - size: Size of the object
// Returns a dynamically allocated byte array containing the serialized data
unsigned char* serialize(const void* obj, size_t size);

// Deserializes a byte array into an object
// Parameters:
// - data: Pointer to the serialized byte array
// - size: Size of the byte array
// - obj: Pointer to the object to deserialize into
// Returns 0 on success, or a non-zero error code on failure
int deserialize(const unsigned char* data, size_t size, void* obj);

// Frees a serialized byte array
// Parameters:
// - data: Pointer to the serialized byte array
void free_serialized_data(unsigned char* data);

#ifdef __cplusplus
}
#endif

#endif // SERIALIZATION_H