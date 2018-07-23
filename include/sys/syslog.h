#ifndef __SYSLOG_H
#define __SYSLOG_H

#include <stdint.h>

typedef struct {
    uint8_t type;
    uint8_t value;
} sysmsg_t;

typedef struct {
    sysmsg_t messages[32];
} syslog_t;

enum {
    END_LOG,
    KERNEL_VER,
    FEATURE_NOT_SUPPORTED
};

#endif