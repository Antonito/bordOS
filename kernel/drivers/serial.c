#include "arch/arch.h"
#include "drivers/serial.h"

void serial_init(const uint16_t port)
{
  outb(port + 1, 0x00); // Disable all interrupts
  outb(port + 3, 0x80); // Enable DLAB (set baud rate divisor)
  outb(port + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
  outb(port + 1, 0x00); //                  (hi byte)
  outb(port + 3, 0x03); // 8 bits, no parity, one stop bit
  outb(port + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  outb(port + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

static int32_t serial_received(const uint16_t port)
{
  return (inb(port + 5) & 1);
}

char serial_read(const uint16_t port)
{
  while (!serial_received(port));
  return (inb(port));
}

static int32_t serial_is_transmit_empty(const uint16_t port)
{
  return (inb(port + 5) & 0x20);
}

void serial_put(const uint16_t port, const char a)
{
  while (!serial_is_transmit_empty(port));
  outb(port, a);
}

/* Writes a NUL-terminated string */
void serial_write(const uint16_t port, const char *const str)
{
  uint32_t i;

  i = 0;
  while (str[i])
    {
      serial_put(port, str[i]);
      if (str[i] == '\n')
	serial_put(port, '\r');
      ++i;
    }
  /* Active wait */
  while (!serial_is_transmit_empty(port));
}

/* Write len characters of the str string */
void serial_write_len(const uint16_t port, const char *const str,
                       const size_t len)
{
  size_t i;

  i = 0;
  while (i < len)
    {
      serial_put(port, str[i]);
      if (str[i] == '\n')
	serial_put(port, '\r');
      ++i;
    }
  /* Active wait */
  while (!serial_is_transmit_empty(port));
}
