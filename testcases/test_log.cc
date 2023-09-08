#include <pthread.h>
#include "amadeusRPC/common/log.h"

void* fun(void*) {

    DEBUGLOG("This is thread in %s", "fun");
    return NULL;
}

int main() {

    pthread_t thread;
    pthread_create(&thread, NULL, &fun, NULL);

    DEBUGLOG("test log %s", "11");
    return 0;
}