#include "arch/arch.h"
#include "lib/lib.h"
#include "logger.h"

__attribute__((noreturn)) void system_abort(const char *const msg,
                                            const char *const file,
                                            const char *const line)
{
  (void)msg, (void)file, (void)line;
  clear_interrupts();
  logger_set_level(LOG_CRITICAL);
  logger_write("System aborted.\n");
  for (;;)
    {
      halt();
    }
}