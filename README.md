# SLog Library

A simple logging library for Arduino with log levels.

## Features

- Log levels: DEBUG, INFO, WARNING, ERROR
- Print and println methods
- printf-style formatted output
- Easy to use static class

## Installation

1. Download the library
2. Place in your Arduino libraries folder
3. Include in your sketch: `#include <SLog.h>`

## Usage

```cpp
#include <SLog.h>

void setup() {
  SLog::begin(115200);
  
  // Set log level
  SLog::setLogLevel(SLog::INFO);
  
  // Log messages
  SLog::debug("Debug message");
  SLog::info("Info message");
  SLog::warning("Warning message");
  SLog::error("Error message");
  
  // Formatted output
  int value = 42;
  SLog::infof("Value: %d", value);
}

void loop() {
  // Your code here
}

API
SLog::begin(baud) - Initialize serial communication

SLog::setLogLevel(level) - Set minimum log level

SLog::print(data, level) - Print without newline

SLog::println(data, level) - Print with newline

SLog::debug(data) - Debug level message

SLog::info(data) - Info level message

SLog::warning(data) - Warning level message

SLog::error(data) - Error level message

SLog::debugf(format, ...) - Formatted debug

SLog::infof(format, ...) - Formatted info

SLog::warningf(format, ...) - Formatted warning

SLog::errorf(format, ...) - Formatted error