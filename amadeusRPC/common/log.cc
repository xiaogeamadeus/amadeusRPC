#include <sys/time.h>
#include <sstream>
#include <stdio.h>
#include "amadeusRPC/common/log.h"
#include "amadeusRPC/common/util.h"
#include "amadeusRPC/common/config.h"


namespace amadeusrpc {

static Logger* g_logger = NULL;

Logger* Logger::GetGlobalLogger() {
    return g_logger;
}

void Logger::InitGlobalLogger() {
    LogLevel global_log_level = StringToLogLevel(Config::GetGlobalConfig()->m_log_level);
    g_logger = new Logger(global_log_level);
}


std::string LogLevelToString(LogLevel level) {
    switch (level) {
        case Debug:
            return "DEBUG";
        case Info:
            return "INFO";
        case Error:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

LogLevel StringToLogLevel(const std::string& log_level) {
    if (log_level == "DEBUG") {
        return Debug;
    } else if (log_level == "INFO") {
        return Info;
    } else if (log_level == "ERROR") {
        return Error;
    } else {
        return Unknown;
    }
}

std::string LogEvent::toString() {
    struct timeval now_time;

    gettimeofday(&now_time, nullptr);

    struct tm now_time_t;
    localtime_r(&(now_time.tv_sec), &now_time_t);

    char buf[128];
    strftime(&buf[0], 128, "%y-%m-%d %H:%M:%S", &now_time_t);
    std::string time_str(buf);

    int ms = now_time.tv_usec / 1000;
    time_str = time_str + "." + std::to_string(ms);

    m_pid = getPid();
    m_thread_id = getThreadId();


    std::stringstream ss;

    ss << "[" << LogLevelToString(m_level) << "]\t"
    << "[" << time_str << "]\t"
    << "[" << m_pid << ":" << m_thread_id << "]\t"
    << "[" << std::string(__FILE__) << ":" << __LINE__ <<"]\t";

    return ss.str();
}

void Logger::pushLog(const std::string& msg) {
    m_buffer.push(msg);
}

void Logger::log() {
    while (!m_buffer.empty()) {
        std::string msg = m_buffer.front();
        m_buffer.pop();

        printf(msg.c_str());
    }
}

}