#include "drivers/cmos.h"
#include "logger.h"

static const struct
{
  const char * str;
  const size_t len;
} _level[] = {{"[DEBUG] ", sizeof("[DEBUG] ") - 1},
              {"INFO] ", sizeof("INFO] ") - 1},
              {"[WARN] ", sizeof("[WARN] ") - 1},
              {"[ERR] ", sizeof("[ERR] ") - 1},
              {"[CRIT] ", sizeof("[CRIT] ") - 1}};

static struct
{
  enum SERIAL_PORT port;
  enum LogLevel    level;
} logger;

void init_logger(const enum SERIAL_PORT port)
{
  logger.port = port;
  logger.level = LOG_DEBUG;
  serial_init(port);
  logger_write("Logger inited\n");
}

void logger_set_level(const enum LogLevel lvl)
{
  if (lvl >= 0 && lvl <= LOG_CRITICAL)
    {
      logger.level = lvl;
    }
}

void logger_write_lvl(const char *const str, const enum LogLevel lvl)
{
  if (lvl <= LOG_CRITICAL && lvl >= logger.level)
    {
      const enum LogLevel save_lvl = logger.level;
      logger_set_level(lvl);
      logger_write(str);
      logger_set_level(save_lvl);
    }
}

static void logger_write_date(void)
{
  cmos_rtc_t date;

  cmos_RTC(&date);
  serial_write_nb(logger.port, date.hour, 10);
  serial_write_len(logger.port, ":", 1);
  serial_write_nb(logger.port, date.minuts, 10);
  serial_write_len(logger.port, ":", 1);
  serial_write_nb(logger.port, date.seconds, 10);
  serial_write_len(logger.port, " ", 1);
}

void logger_write(const char *const str)
{
  logger_write_date();
  serial_write_len(logger.port, _level[logger.level].str,
                   _level[logger.level].len);
  serial_write(logger.port, str);
}
