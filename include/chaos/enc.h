#ifndef ENC_H
#define ENC_H

#include <chaos/gen.h>
#include <stddef.h>

void cipher(struct gen *g, uint8_t *buf, size_t len);

#endif
