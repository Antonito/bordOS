#include "boot/multiboot.h"
#include "memory/pmm.h"
#include "lib/lib.h"
#include "logger.h"

/*
** Physical memory manager implemented as a bitmap
** TODO : Implement as a stack for better performances ? ( O(1) insert ?)
*/

static size_t available_memory_kb;

void init_pmm(mboot_info_t const *const mb)
{
  kassert(mb && "Multiboot header cannot be nullptr");
  // Detect whole memory
  available_memory_kb = (mb->mem_lower) + (mb->mem_upper);
  logger_writef("We have: %dKB | %dMB of memory\n", available_memory_kb,
                available_memory_kb / 1024);

  // Set already used chunks
  logger_write("PMM init'ed\n");
}