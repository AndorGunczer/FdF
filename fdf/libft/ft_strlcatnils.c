#include "libft.h"

unsigned long  ft_strlcatnils(char *dest, const char *src, unsigned long size)
{
  unsigned long dstlen = strlen(dest);
  unsigned long i = 0;
  unsigned long n = 0;
  if (size == 0)
    return(strlen(src));
  while (i < size && i < dstlen)
    i++;
  while (n < size - dstlen - 1 && src[n] != '\0')
  {
    if (i >= size)
      return (strlen(src) + i);
    dest[i + n] = src[n]; // size to ft_strlen(dest)
    n++;
  }
  return(i + strlen(src));
}

    // if (i < dstsize)
    //   return (strlen(src) + i); dstsize + srclen

