#ifndef AMADEUSRPC_COMMON_UTIL_H
#define AMADEUSRPC_COMMON_UTIL_H

#include <sys.types.h>
#include <unistd.h>

namespace amadeusrpc {

pid_t getPid();

pid_t getThreadId();


}

#endif