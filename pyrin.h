#ifndef PYRIN_H
#define PYRIN_H

#include <stdint.h>

void ps_rand(char *);
uint64_t p_rand(void);
char *ltostr(uint64_t, unsigned);
uint64_t micro_hash(char *);
uint8_t *to_hex(uint8_t *);
char *dechex(unsigned, char *, int, int);
uint8_t *pyrin(char *);

#endif
