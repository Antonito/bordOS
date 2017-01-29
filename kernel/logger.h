#ifndef LOGGER_H_
#define LOGGER_H_

#include "drivers/serial.h"

void	init_logger(const enum SERIAL_PORT port);
void	logger_write(const char * const str);

#endif /* !LOGGER_H_ */
