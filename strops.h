#ifndef STROPS_H
#define STROPS_H

#include <stdint.h>

char *ltostr(uint64_t, unsigned);
uint8_t *to_hex(uint8_t *);
char *dechex(unsigned, char *, int, int);
void left_rotate(uint8_t *, int);

#endif