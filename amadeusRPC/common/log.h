#ifndef AMADEUSRPC_COMMON_LOG_H
#define AMADEUSRPC_COMMON_LOG_H

#include <string>
#include <queue>
#include <memory>

#include "amadeusRPC/common/config.h"

namespace amadeusrpc {


template<typename... Args>
std::string formatString(const char* str, Args&&... args) {
    int size = snprintf(nullptr, 0, str, args...);

    std::string result;
    if (size > 0) {
        result.resize(size);
        snprintf(&result[0], size + 1, str, args...);
    }

    return result;
}

#define DEBUGLOG(str, ...) \
    if (amadeusrpc::Logger::GetGlobalLogger()->getLogLevel() <= amadeusrpc::Debug) \
    {                      \
        amadeusrpc::Logger::GetGlobalLogger()->pushLog((new amadeusrpc::LogEvent(amadeusrpc::LogLevel::Debug))->toString() + amadeusrpc::formatString(str, ##__VA_ARGS__) + "\n"); \
        amadeusrpc::Logger::GetGlobalLogger()->log();                              \
    }                      \

#define INFOLOG(str, ...) \
    if (amadeusrpc::Logger::GetGlobalLogger()->getLogLevel() <= amadeusrpc::Info) \
    {                      \
        amadeusrpc::Logger::GetGlobalLogger()->pushLog((new amadeusrpc::LogEvent(amadeusrpc::LogLevel::Info))->toString() + amadeusrpc::formatString(str, ##__VA_ARGS__) + "\n"); \
        amadeusrpc::Logger::GetGlobalLogger()->log();                              \
    }                     \

#define ERRORLOG(str, ...) \
    if (amadeusrpc::Logger::GetGlobalLogger()->getLogLevel() <= amadeusrpc::Error) \
    {                      \
        amadeusrpc::Logger::GetGlobalLogger()->pushLog((new amadeusrpc::LogEvent(amadeusrpc::LogLevel::Error))->toString() + amadeusrpc::formatString(str, ##__VA_ARGS__) + "\n"); \
        amadeusrpc::Logger::GetGlobalLogger()->log();                              \
    } \



enum LogLevel {
    Unknown = 0,
    Debug = 1,
    Info = 2,
    Error = 3
};

class Logger {
public:
    typedef std::shared_ptr<Logger> s_ptr;

    Logger(LogLevel level) : m_set_level(level) {};

    void pushLog(const std::string& msg);

    void log();

    LogLevel getLogLevel() const {
        return m_set_level;
    }
public:
    static Logger* GetGlobalLogger();

    static void InitGlobalLogger();
private:
    LogLevel m_set_level;

    std::queue<std::string> m_buffer;
};

std::string LogLevelToString(LogLevel level);

LogLevel StringToLogLevel(const std::string& log_level);

class LogEvent {
 public:
  LogEvent(LogLevel level) : m_level(level) {}
  std::string getFileName() const {
      return m_file_name;
  }

  LogLevel getLogLevel() const {
      return m_level;
  }

  std::string toString();

 private:
  std::string m_file_name; // File name
  int32_t m_file_line; // File line
  int32_t m_pid; // Process id
  int32_t m_thread_id; // Thread id

  LogLevel m_level; // Log level

};


}


#endif