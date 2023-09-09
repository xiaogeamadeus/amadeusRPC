#include <pthread.h>
#include "amadeusRPC/common/log.h"
#include "amadeusRPC/common/config.h"

void* fun(void*) {
    DEBUGLOG("debug This is thread in %s", "fun");
    INFOLOG("info This is thread in %s", "fun");
    return NULL;
}

int main() {

    amadeusrpc::Config::SetGlobalConfig("../conf/amadeusrpc.xml");
    amadeusrpc::Logger::InitGlobalLogger();


    pthread_t thread;
    pthread_create(&thread, NULL, &fun, NULL);

    DEBUGLOG("test debug log %s", "11");
    INFOLOG("test info log %s", "11");
    return 0;
}