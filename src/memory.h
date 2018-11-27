#ifndef logdisplay_memory_h
#define logdisplay_memory_h

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#endif
