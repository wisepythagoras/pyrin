#ifndef PYRIN_H
#define PYRIN_H

#include <stdint.h>

typedef struct {
    char *seed;
} PyrinContext;

void p_rand_init(PyrinContext *, char *);
uint64_t p_rand(PyrinContext *);
uint64_t m_djb_hash(char *);
uint8_t *pyrin(char *);

#endif
