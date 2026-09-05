#include "SLog.h"

// Initialize static members
SLog::LogLevel SLog::currentLevel = SLog::INFO;
bool SLog::showTimestamp = true;
time_t SLog::cachedSecond = 0;
struct tm SLog::cachedTm = {};
char SLog::cachedTimeStr[32] = {};
char SLog::cachedTzStr[8] = {};

const char* SLog::levelStrings[] = {
  "DEBUG",
  "INFO",
  "WARN",
  "ERROR"
};

void SLog::begin(unsigned long baud) {
  Serial.begin(baud);
  infof("SLog initialized at %lu baud \n", baud);
}

void SLog::setLogLevel(LogLevel level) {
  currentLevel = level;
  infof("Log level set to: %s \n", levelStrings[level]);
}

void SLog::setTimestampEnabled(bool enabled) {
  showTimestamp = enabled;
}

SLog::LogLevel SLog::getLogLevel() {
  return currentLevel;
}

bool SLog::shouldLog(LogLevel level) {
  return level >= currentLevel;
}

extern long timezone;
extern int daylight;

extern long timezone;
extern int daylight;

void SLog::printTimestamp() {
    if (!showTimestamp) return;

    time_t now = time(nullptr);

    // -------- Fallback before NTP --------
    if (now < 100000) {
        unsigned long s = millis() / 1000;
        Serial.printf("[BOOT %02lu:%02lu] ",
                      (s / 60) % 60,
                      s % 60);
        return;
    }

    if (now != cachedSecond) {
        cachedSecond = now;

        struct tm localTm;
        localtime_r(&now, &localTm);   // MUST be local

        // YYYY-MM-DDTHH:MM
        snprintf(cachedTimeStr, sizeof(cachedTimeStr),
                 "%04u-%02u-%02uT%02u:%02u",
                 (unsigned)(localTm.tm_year + 1900),
                 (unsigned)(localTm.tm_mon + 1),
                 (unsigned)localTm.tm_mday,
                 (unsigned)localTm.tm_hour,
                 (unsigned)localTm.tm_min);

        // DST-aware zone name
        if (localTm.tm_isdst > 0) {
            memcpy(cachedTzStr, "AEDT", 5);
        } else {
            memcpy(cachedTzStr, "AEST", 5);
        }
    }

    Serial.printf("[%s %s] ",
                  cachedTimeStr,
                  cachedTzStr);
}

/*void SLog::printTimestamp() {
  if (!showTimestamp) return;
  
  unsigned long ms = millis();
  unsigned long seconds = ms / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  
  printf(NONE, "[%02lu:%02lu:%02lu.%03lu] ",
         hours % 24, minutes % 60, seconds % 60, ms % 1000);
}*/

void SLog::printLogLevel(LogLevel level) {
  if (level < DEBUG || level > ERROR) return;
  printf(NONE, "[%-5s] ", levelStrings[level]);
}

void SLog::print(const char* data, LogLevel level) {
  if (!shouldLog(level)) return;
  
  printTimestamp();
  printLogLevel(level);
  Serial.print(data);
}

void SLog::println(const char* data, LogLevel level) {
  if (!shouldLog(level)) return;
  
  printTimestamp();
  printLogLevel(level);
  Serial.println(data);
}

/*void SLog::print(String data, LogLevel level) {
  if (!shouldLog(level)) return;
  
  printTimestamp();
  printLogLevel(level);
  Serial.print(data);
}

void SLog::println(String data, LogLevel level) {
  if (!shouldLog(level)) return;
  
  printTimestamp();
  printLogLevel(level);
  Serial.println(data);
}*/

void SLog::printf(LogLevel level, const char* format, ...) {
  if (!shouldLog(level)) return;
  
  if (level != NONE) {
    printTimestamp();
    printLogLevel(level);
  }
  
  va_list args;
  va_start(args, format);
  
  // Safer implementation with heap allocation for large strings
  // First, determine the required size
  va_list args_copy;
  va_copy(args_copy, args);
  size_t needed = vsnprintf(NULL, 0, format, args_copy) + 1;
  va_end(args_copy);
  
  if (needed <= 256) {
    // Use stack buffer for small strings
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    Serial.print(buffer);
  } else {
    // Use heap for large strings to avoid stack overflow
    char* buffer = new char[needed];
    vsnprintf(buffer, needed, format, args);
    Serial.print(buffer);
    delete[] buffer;
  }
  
  va_end(args);
}

// Convenience methods
void SLog::debug(String data) {
  if (!shouldLog(DEBUG)) return;
  printTimestamp();
  printLogLevel(DEBUG);
  Serial.println(data);
}

void SLog::info(String data) {
  if (!shouldLog(INFO)) return;
  printTimestamp();
  printLogLevel(INFO);
  Serial.println(data);
}

void SLog::warning(String data) {
  if (!shouldLog(WARNING)) return;
  printTimestamp();
  printLogLevel(WARNING);
  Serial.println(data);
}

void SLog::error(String data) {
  if (!shouldLog(ERROR)) return;
  printTimestamp();
  printLogLevel(ERROR);
  Serial.println(data);
}

void SLog::debugf(const char* format, ...) {
  if (!shouldLog(DEBUG)) return;
  
  printTimestamp();
  printLogLevel(DEBUG);
  
  va_list args;
  va_start(args, format);
  
  // Safer implementation
  va_list args_copy;
  va_copy(args_copy, args);
  size_t needed = vsnprintf(NULL, 0, format, args_copy) + 1;
  va_end(args_copy);
  
  if (needed <= 256) {
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    Serial.print(buffer);
  } else {
    char* buffer = new char[needed];
    vsnprintf(buffer, needed, format, args);
    Serial.print(buffer);
    delete[] buffer;
  }
  
  va_end(args);
}

void SLog::infof(const char* format, ...) {
  if (!shouldLog(INFO)) return;
  
  printTimestamp();
  printLogLevel(INFO);
  
  va_list args;
  va_start(args, format);
  
  va_list args_copy;
  va_copy(args_copy, args);
  size_t needed = vsnprintf(NULL, 0, format, args_copy) + 1;
  va_end(args_copy);
  
  if (needed <= 256) {
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    Serial.print(buffer);
  } else {
    char* buffer = new char[needed];
    vsnprintf(buffer, needed, format, args);
    Serial.print(buffer);
    delete[] buffer;
  }
  
  va_end(args);
}

void SLog::warningf(const char* format, ...) {
  if (!shouldLog(WARNING)) return;
  
  printTimestamp();
  printLogLevel(WARNING);
  
  va_list args;
  va_start(args, format);
  
  va_list args_copy;
  va_copy(args_copy, args);
  size_t needed = vsnprintf(NULL, 0, format, args_copy) + 1;
  va_end(args_copy);
  
  if (needed <= 256) {
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    Serial.print(buffer);
  } else {
    char* buffer = new char[needed];
    vsnprintf(buffer, needed, format, args);
    Serial.print(buffer);
    delete[] buffer;
  }
  
  va_end(args);
}

void SLog::errorf(const char* format, ...) {
  if (!shouldLog(ERROR)) return;
  
  printTimestamp();
  printLogLevel(ERROR);
  
  va_list args;
  va_start(args, format);
  
  va_list args_copy;
  va_copy(args_copy, args);
  size_t needed = vsnprintf(NULL, 0, format, args_copy) + 1;
  va_end(args_copy);
  
  if (needed <= 256) {
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    Serial.print(buffer);
  } else {
    char* buffer = new char[needed];
    vsnprintf(buffer, needed, format, args);
    Serial.print(buffer);
    delete[] buffer;
  }
  
  va_end(args);
}