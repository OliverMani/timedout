#ifndef TIMEDOUT_CONFIGURE_H
#define TIMEDOUT_CONFIGURE_H

#include <stdio.h>
#include "bool.h"
/**
 * Configuration object, which confains settings for the process
 */
struct config {
    bool is_clock;
    bool include_ms;
    const char *format;
};

/**
 * Fill the configuration
 */
void timedout_configure(struct config *config, int argc, char **argv);

#endif