#ifndef logdisplay_message_h
#define logdisplay_message_h

typedef struct {
    char *message;
    int message_len;
} LogEntry;

void initLogEntry(LogEntry *entry);
void writeLogEntry(LogEntry *entry, const char *message);
void freeLogEntry(LogEntry *entry);

#endif
