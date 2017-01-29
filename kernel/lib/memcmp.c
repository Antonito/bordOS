/*
** my_memcmp.c for string.h in /home/bache_a/work/Perso/utils/strings
**
** Made by Antoine Baché
** Login   <bache_a@epitech.net>
**
** Started on  Sun Aug 21 20:46:13 2016 Antoine Baché
** Last update Wed Aug 24 20:38:17 2016 Antoine Baché
*/

#include <stdint.h>
#include <string.h>

int32_t memcmp(const void *s1, const void *s2, size_t n)
{
  unsigned char *s1_cmp;
  unsigned char *s2_cmp;

  s1_cmp = (unsigned char *)s1;
  s2_cmp = (unsigned char *)s2;
  if (!n)
    return (0);
  while (--n)
    {
      if (s1_cmp[n] != s2_cmp[n])
	return ((s1_cmp[n] < s2_cmp[n]) ? -1 : 1);
    }
  if (s1_cmp[0] != s2_cmp[0])
    return ((s1_cmp[n] < s2_cmp[n]) ? -1 : 1);
  return (0);
}
