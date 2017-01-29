#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdint.h>
#include <stddef.h>

/* Serial ports */
enum SERIAL_PORT
  {
    SERIAL_COM1	= 0x3F8,
    SERIAL_COM2	= 0x2F8,
    SERIAL_COM3	= 0x3E8,
    SERIAL_COM4 = 0x2E8
  };

/* Initialization */
void		serial_init(const uint16_t port);

/* Output functons */
void		serial_put(const uint16_t port, const char a);
void		serial_write(const uint16_t port, const char * const str);
void		serial_write_len(const uint16_t port, const char * const str,
				  const size_t len);

/* Input functions */
char		serial_read(const uint16_t port);

#endif /* !SERIAL_H_ */
