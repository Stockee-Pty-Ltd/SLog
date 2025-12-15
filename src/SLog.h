#ifndef SLOG_H
#define SLOG_H

#include <Arduino.h>

class SLog {
  public:
    // Log levels
    enum LogLevel {
      DEBUG = 0,
      INFO = 1,
      WARNING = 2,
      ERROR = 3,
      NONE = 4  // No logging
    };

    // Core logging methods
    static void print(const char* data, LogLevel level = INFO);
    static void println(const char* data, LogLevel level = INFO);
    static void printf(LogLevel level, const char* format, ...);
    
    // Convenience methods for different log levels
    static void debug(String data);
    static void info(String data);
    static void warning(String data);
    static void error(String data);
    
    // Formatted convenience methods
    static void debugf(const char* format, ...);
    static void infof(const char* format, ...);
    static void warningf(const char* format, ...);
    static void errorf(const char* format, ...);
    
    // Configuration methods
    static void begin(unsigned long baud = 115200);
    static void setLogLevel(LogLevel level);
    static void setTimestampEnabled(bool enabled);
    static LogLevel getLogLevel();
    
    // Static members
    static LogLevel currentLevel;
    static bool showTimestamp;

  private:
    static void printTimestamp();
    static void printLogLevel(LogLevel level);
    static bool shouldLog(LogLevel level);
    
    // Constants for formatting
    static const char* levelStrings[];
};

#endif