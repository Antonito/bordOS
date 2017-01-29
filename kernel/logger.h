#ifndef LOGGER_H_
#define LOGGER_H_

#include "drivers/serial.h"

enum LogLevel
{
  LOG_DEBUG = 0,
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR,
  LOG_CRITICAL
};

void init_logger(const enum SERIAL_PORT port);
void logger_set_level(const enum LogLevel lvl);
void logger_write(const char *const str);
void logger_write_lvl(const char *const str, const enum LogLevel lvl);

#endif /* !LOGGER_H_ */
