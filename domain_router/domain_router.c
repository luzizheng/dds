#include "domain_router.h"
#include <stdlib.h>
#include <string.h>

static uint8_t current_domain_id = 0;

int domain_router_set_domain(uint8_t domain_id) {
    if (domain_id > MAX_DOMAIN_ID) {
        return -1; // Invalid domain ID
    }
    current_domain_id = domain_id;
    return 0;
}

int domain_router_filter(uint8_t domain_id) {
    return (domain_id == current_domain_id) ? 1 : 0;
}