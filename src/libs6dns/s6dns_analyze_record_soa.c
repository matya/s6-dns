/* ISC license. */

#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/genwrite.h>
#include <s6-dns/s6dns-message.h>
#include <s6-dns/s6dns-fmt.h>
#include <s6-dns/s6dns-analyze.h>

int s6dns_analyze_record_soa (genwrite_t *gp, s6dns_message_rr_t const *rr, char const *packet, unsigned int packetlen, unsigned int start)
{
  s6dns_message_rr_soa_t soa ;
  char buf[S6DNS_FMT_SOA] ;
  unsigned int pos = start ;
  unsigned int len ;
  if (!s6dns_message_get_soa(&soa, packet, packetlen, &pos)) return 0 ;
  if (rr->rdlength != pos - start) return (errno = EPROTO, 0) ;
  len = s6dns_fmt_soa(buf, S6DNS_FMT_SOA, &soa) ;
  if (!len) return 0 ;
  if ((*gp->put)(gp->target, buf, len) < 0) return 0 ;
  return 1 ;
}
