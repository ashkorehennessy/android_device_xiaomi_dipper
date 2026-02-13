#ifndef	_CIRBUF_H_
#define	_CIRBUF_H_

struct cirbuf_s
{
	unsigned int	idx;
	unsigned int	odx;
	unsigned int	s_len;
	unsigned int	r_len;
	unsigned int	max_len;
	unsigned int    item_cnt;
	unsigned char	*cbuf;
};
typedef  struct cirbuf_s savi_circ_buf;

void cirbuf_init_lhdcv4( struct cirbuf_s *pcb, unsigned char *buf, unsigned int len);

void cirbuf_reset_lhdcv4( struct cirbuf_s *pcb);

unsigned int cirbuf_len_lhdcv4( struct cirbuf_s *pcb);
unsigned int cirbuf_empty_len_lhdcv4( struct cirbuf_s *pcb);
unsigned int cirbuf_get_cnt_lhdcv4( struct cirbuf_s *pcb);

int cirbuf_get_lhdcv4( struct cirbuf_s *pcb, unsigned char *buf, unsigned int len, unsigned int cnt);
int cirbuf_put_lhdcv4( struct cirbuf_s *pcb, unsigned char *buf, unsigned int len, unsigned int cnt);

#endif	/* _CIRBUF_H_ */

