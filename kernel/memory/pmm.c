#include <stdbool.h>
#include "boot/multiboot.h"
#include "memory/pmm.h"
#include "lib/lib.h"
#include "logger.h"

/*
** Physical memory manager implemented as a bitmap
** TODO : Implement as a stack for better performances ? ( O(1) insert ?)
*/
#define BLOCK_PER_BYTE 8
#define BLOCK_SIZE 4096
#define BLOCK_ALIGN BLOCK_SIZE

static size_t    available_memory_kb = 0;
static size_t    pmm_block_total = 0;
static size_t    pmm_block_used = 0;
static uint32_t *pmm_map = NULL;

static inline void pmm_map_set(uint32_t const bit)
{
  pmm_map[bit >> 3] |= (1 << (bit & 7));
}

static inline void pmm_map_unset(uint32_t const bit)
{
  pmm_map[bit >> 3] &= ~(1 << (bit & 7));
}

static inline bool pmm_map_test(uint32_t const bit)
{
  return (pmm_map[bit >> 3] & (1 << (bit & 7)));
}

/* Allows to allocate an area */
static void pmm_init_region(uintptr_t base, size_t size)
{
  base /= BLOCK_SIZE;
  size /= BLOCK_SIZE;
  while (size)
    {
      pmm_map_unset(base);
      --pmm_block_used;
      ++base;
      --size;
    }
}

/* Forbids to allocate an area */
static void pmm_deinit_region(uintptr_t base, size_t size)
{
  base /= BLOCK_SIZE;
  size /= BLOCK_SIZE;
  while (size)
    {
      pmm_map_set(base);
      ++pmm_block_used;
      ++base;
      --size;
    }
}

static intptr_t pmm_get_first_free(void)
{
  for (size_t i = 0; i < pmm_block_total; ++i)
    {
      if (pmm_map[i] != 0xFFFFFFFF)
	{
	  for (int8_t j = 0; j < 32; ++i)
	    {
	      if (pmm_map[i] & (1 << j))
		{
		  return ((i << 5) + j);
		}
	    }
	}
    }
  return (-1);
}

void *pmm_alloc(void)
{
  intptr_t block;

  if (pmm_block_used == pmm_block_total)
    {
      /* No more memory ! */
      return (NULL);
    }
  block = pmm_get_first_free();
  kassert(block != -1 && "Wrong handling of memory");
  ++pmm_block_total;
  return ((void *)(block * BLOCK_SIZE));
}

void pmm_free(void const *const ptr)
{
  uintptr_t _ptr = (uintptr_t)ptr;
  bool      is_set = pmm_map_test(_ptr);

  pmm_map_unset(_ptr / BLOCK_SIZE);
  if (is_set)
    {
      --pmm_block_used;
      kassert(pmm_block_used <= pmm_block_total &&
              "BlockUsed cannot be more than total blocks");
    }
}

void init_pmm(mboot_info_t const *const mb)
{
  extern uintptr_t _end; /* End of kernel */

  kassert(mb && "Multiboot header cannot be nullptr");
  kassert((mb->flags & (1 << 0)) && "Bit 0 of flags mut be set !");

  // Detect whole memory
  available_memory_kb = (mb->mem_lower) + (mb->mem_upper);
  pmm_block_total = (available_memory_kb * 1024) / BLOCK_SIZE;
  pmm_block_used = 0;
  pmm_deinit_region(0, available_memory_kb * 1024);
  pmm_map = (uint32_t *)_end;
  pmm_init_region(_end + pmm_block_total,
                  available_memory_kb * 1024 - _end / 1024);
  logger_writef("We have: %dKB | %dMB of memory\n", available_memory_kb,
                available_memory_kb / 1024);
  logger_writef("Total Blocks: %d | Used: %d\n", pmm_block_total,
                pmm_block_used);
  logger_writef("Available memory: %dKB | %dMB\n",
                ((pmm_block_total - pmm_block_used) * BLOCK_SIZE) / 1024,
                ((pmm_block_total - pmm_block_used) * BLOCK_SIZE) / 1024 /
                    1024);
  // Set already used chunks
  logger_write("PMM init'ed\n");
}
