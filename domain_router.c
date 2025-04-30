/*
 * @Author: LuZizheng lu.zizheng@byd.com
 * @Date: 2025-04-30 09:12:54
 * @LastEditors: LuZizheng lu.zizheng@byd.com
 * @LastEditTime: 2025-04-30 09:56:48
 * @FilePath: /Dinix/bydos/lib/dds/domain_router.c
 * @Description: 
 * 
 * Copyright (c) 2025 by BYD, All Rights Reserved. 
 */
#include "domain_router.h"
#include <stdlib.h>
#include <string.h>
#include "gcydds.h"

static uint8_t current_domain_id = 0;

int domain_router_set_domain(uint8_t domain_id) {
    if (domain_id > DDS_MAX_DOMAIN_ID) {
        return -1; // Invalid domain ID
    }
    current_domain_id = domain_id;
    return 0;
}

int domain_router_filter(uint8_t domain_id) {
    return (domain_id == current_domain_id) ? 1 : 0;
}