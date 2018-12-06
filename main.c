/*
 * Copyright (c) 2016-2018 . All Rights Reserved.
 */

#include "xdr.h"
#include "stellar.h"
#include <string.h>
#include <stdio.h>

uint8_t strtohex(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return 255;
}

int hex2byte_arr(char *buf, int len, uint8_t *out, int outbuf_size) {
    int i = len - 1;
    int out_len = (len & 1) ? (len + 1) / 2 : len / 2;
    int j = out_len - 1;

    if (j > outbuf_size)
        return -1; /* Output buffer is smaller than need */

    while (i >= 0) {
        out[j] = strtohex(buf[i--]);
        if (i >= 0) {
            out[j--] |= strtohex(buf[i--]) << 4;
        }
    }

    return out_len;
}

void testCreateAccountOp() {
    char rawTx[1024] = {0,};
    char publicKey[128] = {0,};
    uint8_t publicKeyData[33];
    char signature[256] = {0,};

    StellarSignTx signTx;
    StellarSignedTx signedTx;
    StellarCreateAccountOp createAccountOp;

    strcpy(signTx.source_account, "GDGJ6GB2DV4NQHHOBLONVQBVJRQA7BJSM57UGB5ATKIKBS6SOIU6O5GK");
    signTx.has_source_account = true;
    signTx.fee = 100;
    signTx.has_fee = true;

    signTx.sequence_number = 6;
    signTx.has_sequence_number = true;

    signTx.memo_type = 0;
    signTx.has_memo_type = true;

    signTx.has_num_operations = true;
    signTx.num_operations = 1;

    strcpy(signTx.network_passphrase, "Public Global Stellar Network ; September 2015");
    signTx.has_network_passphrase = true;

    createAccountOp.has_new_account = true;
    createAccountOp.has_starting_balance = true;
    createAccountOp.has_source_account = true;

    strcpy(createAccountOp.new_account, "GBF3FJMLBO3BR7IIHYQAPSHKZ7XZ7DZ4HQ4FXLVNNJZTXMS45MPMM2C2");
    createAccountOp.starting_balance = 500111000;
    strcpy(createAccountOp.source_account, "GDGJ6GB2DV4NQHHOBLONVQBVJRQA7BJSM57UGB5ATKIKBS6SOIU6O5GK");

    strcpy(publicKey, "019139E6F6625C403132C9B8DF75844CDA34221327E3996385FC7A693966CB7E57");
    hex2byte_arr(publicKey, 66, publicKeyData, 33);

    strcpy(signature, "D01ECBBB0498BD881A37E13C02BAA8D301B3DC137FE22ABA46D86556326DCB0ACEB608D4121AC127DE4AF2878DF1CA7E6DAE236A4CA257E5D00562FFCA75A80A");
    hex2byte_arr(signature, 128, signedTx.signature.bytes, 64);
    hex2byte_arr(publicKey, 64, signedTx.public_key.bytes, 32);

    envelopeXdrBase64(publicKeyData, &signTx, &signedTx, &createAccountOp, NULL, rawTx);
    printf("create account raw Tx: %s\n", rawTx);
}

void testPaymentOp() {
    char rawTx[1024] = {0,};
    char publicKey[128] = {0,};
    uint8_t publicKeyData[33];
    char signature[256] = {0,};

    StellarSignTx signTx;
    StellarSignedTx signedTx;
    StellarPaymentOp paymentOp;

    strcpy(signTx.source_account, "GDGJ6GB2DV4NQHHOBLONVQBVJRQA7BJSM57UGB5ATKIKBS6SOIU6O5GK");
    signTx.has_source_account = true;
    signTx.fee = 100;
    signTx.has_fee = true;

    signTx.sequence_number = 6;
    signTx.has_sequence_number = true;

    signTx.memo_type = 0;
    signTx.has_memo_type = true;

    signTx.has_num_operations = true;
    signTx.num_operations = 1;

    strcpy(signTx.network_passphrase, "Public Global Stellar Network ; September 2015");
    signTx.has_network_passphrase = true;

    paymentOp.has_destination_account = true;
    paymentOp.has_amount = true;
    paymentOp.has_source_account = true;

    strcpy(paymentOp.destination_account, "GBF3FJMLBO3BR7IIHYQAPSHKZ7XZ7DZ4HQ4FXLVNNJZTXMS45MPMM2C2");

    paymentOp.amount = 500111000;

    strcpy(paymentOp.source_account, "GDGJ6GB2DV4NQHHOBLONVQBVJRQA7BJSM57UGB5ATKIKBS6SOIU6O5GK");
    StellarAssetType asset;
    asset.type = 0;
    paymentOp.asset = asset;

    strcpy(publicKey, "019139E6F6625C403132C9B8DF75844CDA34221327E3996385FC7A693966CB7E57");
    hex2byte_arr(publicKey, 66, publicKeyData, 33);


    strcpy(signature, "D01ECBBB0498BD881A37E13C02BAA8D301B3DC137FE22ABA46D86556326DCB0ACEB608D4121AC127DE4AF2878DF1CA7E6DAE236A4CA257E5D00562FFCA75A80A");
    hex2byte_arr(signature, 128, signedTx.signature.bytes, 64);
    hex2byte_arr(publicKey, 64, signedTx.public_key.bytes, 32);

    envelopeXdrBase64(publicKeyData, &signTx, &signedTx, NULL, &paymentOp, rawTx);
    printf("payment raw Tx: %s\n", rawTx);
}

int main() {
    testCreateAccountOp();
    testPaymentOp();
    return 0;
}
