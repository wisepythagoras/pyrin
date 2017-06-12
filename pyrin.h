#ifndef PYRIN_H
#define PYRIN_H

#include <stdint.h>

void p_rand_init(char *);
uint64_t p_rand(void);
uint64_t m_djb_hash(char *);
uint8_t *pyrin(char *);

#endif
