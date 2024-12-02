#include <timedout/configure.h>
#include <string.h>
#include <stdlib.h>

void setup_default_configuration(struct config *config) {
    config->is_clock = false;
    config->include_ms = false;
    config->format = DEFAULT_TIME_FORMAT;
}

void print_helppage(char *command) {
    printf("Usage: [some command] | %s [options]\n", command);
    printf("  Options:\n");
    printf("    -c\t\t\tDisplay time as current time instead of how much time has elapsed.\n");
    printf("    -m\t\t\tDisplay milliseconds also.\n");
    // Can also been seen via https://www.man7.org/linux/man-pages/man3/strftime.3.html
    printf("    -f [format]\t\tDisplay as custom format, based on strftime. See man 3 strftime.\n");
    exit(0);
}

void timedout_configure(struct config *config, int argc, char **argv) {
    setup_default_configuration(config);
    char *current;
    int i;
    for(i = 1; i < argc; i++) {
        current = argv[i];
        if (!strcmp(current, "-c")) {
            config->is_clock = true;
        } else if (!strcmp(current, "-m")) {
            config->include_ms = true;
        } else if (!strcmp(current, "-f")) {
            config->format = argv[++i];
        } else if (!strcmp(current, "-h") || !strcmp(current, "--help")) {
            print_helppage(argv[0]);
        }
    }
}