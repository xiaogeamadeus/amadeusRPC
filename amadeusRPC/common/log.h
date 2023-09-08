#ifndef AMADEUSRPC_COMMON_LOG_H
#define AMADEUSRPC_COMMON_LOG_H

#include <string>
#include <queue>
#include <memory>

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
    std::string msg = (new amadeusrpc::LogEvent(amadeusrpc::LogLevel::Debug))->toString() + amadeusrpc::formatString(str, ##__VA_ARGS__); \
    msg += "\n";                                                                                                                          \
    amadeusrpc::Logger::GetGlobalLogger()->pushLog(msg);                                                                                  \
    amadeusrpc::Logger::GetGlobalLogger()->log();                                                                                         \

enum LogLevel {
    Debug = 1,
    Info = 2,
    Error = 3
};

class Logger {
public:

    typedef std::shared_ptr<Logger> s_ptr;

    void pushLog(const std::string& msg);

    void log();
public:
    static Logger* GetGlobalLogger();
private:
    LogLevel m_set_level;

    std::queue<std::string> m_buffer;
};

std::string LogLevelToString(LogLevel level);

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