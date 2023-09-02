#ifndef AMADEUSRPC_COMMON_LOG_H
#define AMADEUSRPC_COMMON_LOG_H

#include <string>

namespace amadeusrpc {

template<typename... Args>
std::string formatString(const char* str, Args&&... args) {
    int size = snprintf(nullptr, 0, str, args...);

    std:string result;
    if (size > 0) {
        result.resize(size);
        snprintf(&result[0], size + 1, str, args...);
    }

    return result;
}

enum LogLevel {
    Debug = 1,
    Info = 2,
    Error = 3
};

class LogEvent {
 public:
  std::string getFileName() const {
      return m_file_name;
  }

  LogLevel getLogLevel() const {
      return m_level;
  }

  void printLog();

 private:
  std::string m_file_name; // File name
  int32_t m_file_line; // File line
  int32_t m_pid; // Process id
  int32_t m_thread_id; // Thread id

  LogLevel m_level; // Log level
};
}
#endif