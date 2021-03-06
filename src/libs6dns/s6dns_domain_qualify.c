/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <s6-dns/s6dns-domain.h>

unsigned int s6dns_domain_qualify (s6dns_domain_t *list, s6dns_domain_t const *d, char const *rules, unsigned int rulesnum)
{
  if (!d->len) return (errno = EINVAL, 0) ;
  if (d->s[d->len - 1] == '.')
  {
    list[0] = *d ;
    return 1 ;
  }
  else
  {
    register unsigned int i = 0 ;
    for (; i < rulesnum ; i++)
    {
      unsigned int n = str_len(rules) ;
      if (d->len + n >= 254) return (errno = ENAMETOOLONG, 0) ;
      list[i] = *d ;
      list[i].s[d->len] = '.' ;
      byte_copy(list[i].s + d->len + 1, n, rules) ;
      list[i].len += n+1 ;
      rules += n+1 ;
    }
    return i ;
  }
}
