#include "logger.h"

static struct
{
  enum SERIAL_PORT	port;

} logger;

void	init_logger(const enum SERIAL_PORT port)
{
  logger.port = port;
  serial_init(port);
}

void	logger_write(const char * const str)
{
  serial_write_len(logger.port, "[DEBUG] ", sizeof("[DEBUG] ") - 1);
  serial_write(logger.port, str);
}
