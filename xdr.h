/*
 * Copyright (c) 2016-2018 . All Rights Reserved.
 */

#ifndef CORE_WALLET_XDR_H
#define CORE_WALLET_XDR_H

#include <stdint.h>
#include "stellar.h"

typedef struct uint128_t { uint64_t elements[2]; } uint128_t;

typedef struct uint256_t { uint128_t elements[2]; } uint256_t;

void envelopeXdrBase64(const uint8_t *public_key, const StellarSignTx *signTx, const StellarSignedTx *signedTx, StellarCreateAccountOp *createAccountOp, StellarPaymentOp *paymentOp, char *xdrOutputStream);

#endif //CORE_WALLET_XDR_H
