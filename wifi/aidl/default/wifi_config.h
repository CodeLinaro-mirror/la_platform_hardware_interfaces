/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <string.h>

#ifndef PROPERTY_VALUE_MAX
#define PROPERTY_VALUE_MAX 92
#endif

#define __unused __attribute__ ((__unused__))

#define WIFI_HAL_INTERFACE_COMBINATIONS {{{STA}, 2}}


/* TODO: Local property set/get config functions */
static int property_set(const char *key, const char *value) {
    return 0;
}

static int property_get(const char* key, char* value, const char* default_value)
{
    int len = 0;

    if (default_value) {
        len = strnlen(default_value, PROPERTY_VALUE_MAX - 1);
        memcpy(value, default_value, len);
        value[len] = '\0';
    }

    return len;
}

#endif /* WIFI_CONFIG_H */
