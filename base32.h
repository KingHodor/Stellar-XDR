/*
 * Copyright (c) 2016-2018, Evercoin. All Rights Reserved.
 */

#ifndef XDRPROJECT_BASE32_H
#define XDRPROJECT_BASE32_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern const char *BASE32_ALPHABET_RFC4648;

uint8_t *base32_decode(const char *in, size_t inlen, uint8_t *out, size_t outlen, const char *alphabet);

#endif //XDRPROJECT_BASE32_H
