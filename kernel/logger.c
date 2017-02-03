#include <stdarg.h>
#include "drivers/cmos.h"
#include "lib/lib.h"
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

// TODO: Optimize, do not write character by character
static void logger_writev(const char *const fmt, va_list *ap)
{
  size_t ite = 0;

  kassert(fmt && ap && "Format string and va list cannot be nullptr");
  while (fmt[ite])
    {
      if (fmt[ite] == '%' && fmt[ite + 1])
	{
	  ++ite;
	  switch (fmt[ite])
	    {
	      int32_t     _nb;
	      uint32_t    _nbu;
	      uint32_t    _nbX;
	      char const *_tmp;
	    case 's':
	      _tmp = va_arg(*ap, char *);
	      serial_write(logger.port, _tmp);
	      break;
	    case 'd':
	      _nb = va_arg(*ap, int32_t);
	      serial_write_nb(logger.port, _nb, 10);
	      break;
	    case 'u':
	      _nbu = va_arg(*ap, uint32_t);
	      serial_write_nb(logger.port, _nbu, 10);
	      break;
	    case 'x':
	      _nbX = va_arg(*ap, uint32_t);
	      serial_write_nb(logger.port, _nbX, 16);
	      break;
	    default:
	      kassert(0 && "Not supported format string");
	      break;
	    }
	}
      else
	{
	  serial_write_len(logger.port, &fmt[ite], 1);
	}
      ++ite;
    }
}

static void logger_writef_nodate(const char *const fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  logger_writev(fmt, &ap);
  va_end(ap);
}

static void logger_write_date(void)
{
  static char const *_months[] = {"",     "Jan.", "Fev.", "Mar.", "Apr.",
                                  "May.", "Jun.", "Jul.", "Aug.", "Sep.",
                                  "Oct.", "Nov.", "Dec."};
  cmos_rtc_t date;

  cmos_RTC(&date);
  logger_writef_nodate("%d %s %d:%d:%d ", date.day, _months[date.month],
                       date.hour, date.minuts, date.seconds);
}

void logger_write(const char *const str)
{
  logger_write_date();
  serial_write_len(logger.port, _level[logger.level].str,
                   _level[logger.level].len);
  serial_write(logger.port, str);
}

void logger_writef(const char *const fmt, ...)
{
  va_list ap;

  logger_write_date();
  va_start(ap, fmt);
  logger_writev(fmt, &ap);
  va_end(ap);
}