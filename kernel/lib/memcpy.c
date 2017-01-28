/*
** my_memcpy.c for string.h in /home/bache_a/work/Perso/utils/strings
**
** Made by Antoine Baché
** Login   <bache_a@epitech.net>
**
** Started on  Sun Aug 21 20:52:10 2016 Antoine Baché
** Last update Sun Sep 18 19:08:50 2016 Antoine Baché
*/

#include <string.h>

void *memcpy(void *dest, const void *src, size_t n)
{
  unsigned char *dest_w;
  unsigned char *src_r;

  dest_w = (unsigned char *)dest;
  src_r = (unsigned char *)src;
  --n;
  while (n > 8)
    {
      dest_w[n] = src_r[n];
      dest_w[n - 1] = src_r[n - 1];
      dest_w[n - 2] = src_r[n - 2];
      dest_w[n - 3] = src_r[n - 3];
      dest_w[n - 4] = src_r[n - 4];
      dest_w[n - 5] = src_r[n - 5];
      dest_w[n - 6] = src_r[n - 6];
      dest_w[n - 7] = src_r[n - 7];
      n -= 8;
    }
  while (n)
    {
      dest_w[n] = src_r[n];
      --n;
    }
  dest_w[0] = src_r[0];
  return (dest);
}
