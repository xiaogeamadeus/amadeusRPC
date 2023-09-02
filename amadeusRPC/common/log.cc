#include <sys/time.h>
#include "amadeusRPC/common/log.h"

namespace amadeusrpc {


void LogEvent::printLog() {
    struct timeval now_time;

    gettieofday(&now_time, nullptr);

    struct tm now_time_t;
    localtime_r(&(now_time.tv_sec), &now_time_t);

    char buf[128];
    strftime(&buf[0], 128, "%y-%m-%d %H:%M:%S", &now_time_t);
    std::string time_str(buf);

    int ms = now_time.tv_usec * 1000;
    time_str = time_str + "." + std::to_string(ms);


}


}