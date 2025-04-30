/*
 * @Author: LuZizheng lu.zizheng@byd.com
 * @Date: 2025-04-30 09:16:03
 * @LastEditors: LuZizheng lu.zizheng@byd.com
 * @LastEditTime: 2025-04-30 09:16:07
 * @FilePath: /Dinix/bydos/lib/dds/domain_router.h
 * @Description: 
 * 
 * Copyright (c) 2025 by BYD, All Rights Reserved. 
 */
#ifndef DDS_DOMAIN_ROUTER_H
#define DDS_DOMAIN_ROUTER_H

// Initializes the Domain Router
void initialize_domain_router();

// Routes a message
void route_message(const char* message);

// Shuts down the Domain Router
void shutdown_domain_router();

#endif // DOMAIN_ROUTER_H