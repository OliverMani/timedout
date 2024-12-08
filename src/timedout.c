#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <timedout/bool.h>
#include <timedout/configure.h>

#define BUFFER_CHUNK_SIZE 1024
#define MAX_DATETIME_STRING_LENGTH 64

/*
    Quick function to construct a timeval with current time.
*/
struct timeval get_timeval_now() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv;
}


/*
    Fills the time buffer
*/
void format_time(char *buffer, const char *format, struct timeval *tv, bool add_milliseconds) {
    struct tm *info = localtime(&tv->tv_sec);
    strftime(buffer, MAX_DATETIME_STRING_LENGTH, format, info);
    if(add_milliseconds) {
        size_t len = strlen(buffer);
        int milliseconds = tv->tv_usec / 1000;
        snprintf(buffer + len, MAX_DATETIME_STRING_LENGTH - len, ".%03d", milliseconds);
    }
}

int main(int argc, char **argv) {
    // Configures before running
    struct config config;
    timedout_configure(&config, argc, argv);

    // tells when new line is starting
    bool is_new_line = true;

    // Stream buffer
    char buffer[BUFFER_CHUNK_SIZE + 1];
    buffer[BUFFER_CHUNK_SIZE] = 0;

    // Time format buffer
    char timebuffer[MAX_DATETIME_STRING_LENGTH + 1];
    timebuffer[MAX_DATETIME_STRING_LENGTH] = 0;

    // Time when we start the streaming, only used if clock is disabled
    struct timeval start_tv = get_timeval_now();

    time_t time_elapsed;

    // Reads data, writes to buffer and handles it until the stream is over
    while(fgets(buffer, BUFFER_CHUNK_SIZE, stdin) != NULL) {
        // If there is a new line, print the prefix
        if(is_new_line) {
            struct timeval now = get_timeval_now();
            if(!config.is_clock) {
                time_elapsed = (now.tv_sec - start_tv.tv_sec) * 1000000 + (now.tv_usec - start_tv.tv_usec);
                now.tv_sec   = time_elapsed / 1000000;
                now.tv_usec  = time_elapsed % 1000000;
            }
            format_time(timebuffer, config.format, &now, config.include_ms);
            printf("[%s] ", timebuffer);
            is_new_line = false;
            
        }
        // print the buffer to the stream
        printf("%s", buffer);

        // If the line is ending, remember it is going to be a new line
        if(strchr(buffer, '\n')) 
            is_new_line = true;
    }


    // In the end, print a new line if it is not done by default.
    if(!is_new_line)
        printf("\n");
    
    return 0;
}