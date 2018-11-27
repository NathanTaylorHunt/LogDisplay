#include <stdio.h>
#include <string.h>

#include "connect.h"

int main(int argc, char* argv[]) {
    if (argc == 2 &&strcmp(argv[1], "--heartbeat") == 0) {
        startHeartbeatService();
    } else {
        startDisplay();
    }

    return 0;
}
