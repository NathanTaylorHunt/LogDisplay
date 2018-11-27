#include <stdio.h>
#include <string.h>

#include "connect.h"

int main(int argc, char* argv[]) {
    if (argc == 2 &&strcmp(argv[1], "--server") == 0) {
        server();
    } else {
        loop();
    }

    return 0;
}
