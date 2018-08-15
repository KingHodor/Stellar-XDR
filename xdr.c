/*
 * Copyright (c) 2016-2018, Evercoin. All Rights Reserved.
 */

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "xdr.h"
#include "base64.h"

size_t written = 0;

void incCount(int value) {
    written = written + value;
}

void write(const pb_byte_t *b, int off, int len, pb_byte_t *new_bytes) {
    for (int i = 0; i < len; ++i) {
        new_bytes[written + i] = b[i + off];
    }
    incCount(len);
}

void writeInt(uint32_t v, pb_byte_t *new_bytes) {
    new_bytes[written] = (pb_byte_t) ((v >> 24) & 0xFF);
    new_bytes[written + 1] = (pb_byte_t) ((v >> 16) & 0xFF);
    new_bytes[written + 2] = (pb_byte_t) ((v >> 8) & 0xFF);
    new_bytes[written + 3] = (pb_byte_t) ((v >> 0) & 0xFF);
    incCount(4);
}

void writeLong(uint64_t v, pb_byte_t *new_bytes) {
    pb_byte_t writeBuffer[8];

    writeBuffer[0] = (pb_byte_t) (v >> 56);
    writeBuffer[1] = (pb_byte_t) (v >> 48);
    writeBuffer[2] = (pb_byte_t) (v >> 40);
    writeBuffer[3] = (pb_byte_t) (v >> 32);
    writeBuffer[4] = (pb_byte_t) (v >> 24);
    writeBuffer[5] = (pb_byte_t) (v >> 16);
    writeBuffer[6] = (pb_byte_t) (v >> 8);
    writeBuffer[7] = (pb_byte_t) (v >> 0);
    write(writeBuffer, 0, 8, new_bytes);
}


void envelopeXdrBase64(const uint8_t *public_key, const StellarSignTx *signTx, const StellarSignedTx *signedTx,
                       StellarCreateAccountOp *createAccountOp, StellarPaymentOp *paymentOp, char *xdrOutputStream) {
    size_t out_len = 0;
    written = 0;
    pb_byte_t new_bytes[1024];

    pb_byte_t dest_publicKey[STELLAR_KEY_SIZE];

    writeInt(0, new_bytes); // ED25519 type value
    write(public_key + 1, 0, 32, new_bytes); // public key
    writeInt(signTx->fee, new_bytes);
    writeLong(signTx->sequence_number, new_bytes);
    writeInt(0, new_bytes); // timeBounds is null
    writeInt(signTx->memo_type, new_bytes); // memotype is 0
    writeInt(signTx->num_operations, new_bytes); // operations size
    writeInt(0, new_bytes); // operation sourceAccount is null
    if (createAccountOp != NULL) {
        writeInt(0, new_bytes); // operation type
        writeInt(0, new_bytes); // ED25519 type value
        stellar_getAddressBytes(createAccountOp->new_account, dest_publicKey);
        write(dest_publicKey, 0, 32, new_bytes); // public key
        writeLong((uint64_t) createAccountOp->starting_balance, new_bytes);
    } else if (paymentOp != NULL) {
        writeInt(1, new_bytes); // operation type
        writeInt(0, new_bytes); // ED25519 type value
        stellar_getAddressBytes(paymentOp->destination_account, dest_publicKey);
        write(dest_publicKey, 0, 32, new_bytes); // public key
        writeInt(0, new_bytes); // assetnative
        writeLong((uint64_t) paymentOp->amount, new_bytes);
        writeInt(0, new_bytes); // Transaction Ext
    }
    writeInt(1, new_bytes); // signature size

    write(signedTx->public_key.bytes, 27, 4, new_bytes); // last 4 bytes of the public key, used as a hint
    writeInt(signedTx->signature.size, new_bytes); // signature size
    write(signedTx->signature.bytes, 0, 64, new_bytes); // public key


    char *encoded_data = base64_encode(new_bytes, written, &out_len);
    strcpy(xdrOutputStream, encoded_data);
    free(encoded_data);
}

