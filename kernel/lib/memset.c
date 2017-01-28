/*
** my_memset.c for string.h in /home/bache_a/work/Perso/utils/strings
**
** Made by Antoine Baché
** Login   <bache_a@epitech.net>
**
** Started on  Sun Aug 21 20:55:27 2016 Antoine Baché
** Last update Tue Sep 20 22:54:52 2016 Antoine Baché
*/

#include <stdint.h>
#include <string.h>

void *memset(void *s, int32_t c, size_t n)
{
  unsigned char *dest_w;

  dest_w = (unsigned char *)s;
  --n;
  while (n > 8)
    {
      dest_w[n] = c;
      dest_w[n - 1] = c;
      dest_w[n - 2] = c;
      dest_w[n - 3] = c;
      dest_w[n - 4] = c;
      dest_w[n - 5] = c;
      dest_w[n - 6] = c;
      dest_w[n - 7] = c;
      n -= 8;
    }
  while (n)
    {
      dest_w[n] = c;
      --n;
    }
  dest_w[0] = c;
  return (s);
}
