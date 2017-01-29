#include <stddef.h>
#include "arch/arch.h"
#include "drivers/pit.h"
#include "logger.h"

#define PIT_CH0 0x40    /* Channel 0, IRQ1 */
#define PIT_CH1 0x41    /* Channel 1, DRAM */
#define PIT_CH2 0x42    /* Channel 2, Speaker */
#define PIT_CMDREG 0x43 /* Command Register Port */

static size_t counter = 0;

static void pit_set_speaker(const int32_t hz)
{
  const int32_t val = 1193180 / hz;

  outb(PIT_CMDREG, 0xb6);
  outb(PIT_CH2, (uint8_t)(val));
  outb(PIT_CH2, (uint8_t)(val >> 8));
}

static void pit_set_timer(const int32_t hz)
{
  const int32_t val = 1193180 / hz;

  outb(PIT_CMDREG, 0x36);
  outb(PIT_CH0, val & 0xFF);
  outb(PIT_CH0, val >> 8);
}

static void timer_handler(regs_t *registers)
{
  (void)registers;
  counter++;
}

static void pit_wait(uint32_t count)
{
  size_t delay;

  delay = counter + count;
  while (counter < delay)
    ;
}

static inline void pit_no_sound()
{
  outb(0x61, inb(0x61) & 0xFC);
}

static void pit_play_sound(uint32_t nFrequence)
{
  uint32_t val;
  uint8_t  tmp;

  val = 1193180 / nFrequence;
  outb(0x43, 0xb6);
  outb(0x42, (uint8_t)(val));
  outb(0x42, (uint8_t)(val >> 8));

  // Use the PC speaker
  tmp = inb(0x61);
  if (tmp != (tmp | 3))
    {
      outb(0x61, tmp | 3);
    }
}

void beep()
{
  pit_play_sound(1000);
  pit_wait(10);
  pit_no_sound();
  logger_write("Beeped !\n");
}

void init_timer()
{
  /* 18.22Hz by default, sets it to 100Hz */
  pit_set_timer(100);
  pit_set_speaker(1000);
  irq_set_routine(0, timer_handler);
  logger_write("PIT's timer inited.\n");
}
