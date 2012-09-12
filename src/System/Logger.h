#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <iostream>

#define LogDebug    Logger(__FILE__,__LINE__, Logger::Debug)
#define LogError    Logger(__FILE__,__LINE__, Logger::Error)
#define LogWarning  Logger(__FILE__,__LINE__, Logger::Warning)
#define LogInfo     Logger(__FILE__,__LINE__, Logger::Info)
#define LogFatal    Logger(__FILE__,__LINE__, Logger::Fatal)

using std::string;

class Logger {

public:
  enum LogLevel {
    Debug = 0,
    Info,
    Warning,
    Error,
    Fatal
  };

  Logger(const char* file, int line, LogLevel level);
  Logger(const std::string& file, int line, LogLevel level);
  virtual ~Logger();
  template<class T>
  Logger& operator<< (const T & i) {
    if(print)
      std::cout << i << " ";
    return *this;
  }

  struct nullstr {
    const char * str;
    inline nullstr(const char * s) : str(s) { };
  };

  /* Log a string that may be null. */
  Logger & operator<<(const nullstr & s);

  static LogLevel logLevel;
private:
  bool print, fatal;
  string getSpaces(int count, int line);
  bool isInBlackList(const string& file);
  void writeInfo(const char* file, int line, Logger::LogLevel level);
  LogLevel getLogLevel(const std::string & file);
  void log(int mode, int color, const string & level,
      const string & file, int line);
};
