#include "message.h"

#include <stdlib.h>
#include <string.h>

void initLogEntry(LogEntry *entry) {
    entry->message = NULL;
    entry->message_len = 0;
}

void writeLogEntry(LogEntry *entry, const char *message) {
    entry->message = malloc(sizeof(message));
    strcpy(entry->message, message);
    entry->message_len = strlen(message);
};

void freeLogEntry(LogEntry *entry) {
    free(entry->message);
    initLogEntry(entry);
}
