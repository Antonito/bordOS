#include <string.h>
#include <stdint.h>

size_t strlen(const char *str)
{
  size_t   size;
  uint32_t cur;

  size = 0;
  for (;;)
    {
      cur = *(uint32_t *)str;
      if (!(cur & 0xFF))
	return (size);
      if (!(cur & 0xFF00))
	return (size + 1);
      if (!(cur & 0xFF0000))
	return (size + 2);
      if (!(cur & 0xFF000000))
	return (size + 3);
      str += 4;
      size += 4;
    }
}
