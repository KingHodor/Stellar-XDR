# Stellar XDR C library

XDR, also known as External Data Representation, is used extensively in the Stellar Network, especially in the core protocol. The ledger, transactions, results, history, and even the messages passed between computers running stellar-core are encoded using XDR.

Read more in the [documentation on ReadTheDocs](https://www.stellar.org/developers/horizon/reference/xdr.html). 

## Create an Account: This operation creates and funds a new account with the specified starting balance.
                   
```c
void testCreateAccountOp() {
    char rawTx[1024] = {0,};
    char publicKey[128] = {0,};
    uint8_t publicKeyData[33];

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
    printf("raw Tx: %s\n", rawTx);
}

```

## Payment: Sends an amount in a specific asset to a destination account.
                      
```c
void testPaymentOp() {
    char rawTx[1024] = {0,};
    char publicKey[128] = {0,};
    uint8_t publicKeyData[33];

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
    printf("raw Tx: %s\n", rawTx);
}

```
Output:
```c
create account raw Tx: AAAAAJE55vZiXEAxMsm433WETNo0IhMn45ljhfx6aTlmy35XAAAAZAAAAAAAAAAGAAAAAAAAAAAAAAABAAAAAAAAAAAAAAAAS7Kliwu2GP0IPiAHyOrP75+PPDw4W66tanM7slzrHsYAAAAAHc8WmAAAAAFpOWbLAAAAANAey7sEmL2IGjfhPAK6qNMBs9wTf+IqukbYZVYybcsKzrYI1BIawSfeSvKHjfHKfm2uI2pMolfl0AVi/8p1qAo=

payment raw Tx:        AAAAAJE55vZiXEAxMsm433WETNo0IhMn45ljhfx6aTlmy35XAAAAZAAAAAAAAAAGAAAAAAAAAAAAAAABAAAAAAAAAAEAAAAAS7Kliwu2GP0IPiAHyOrP75+PPDw4W66tanM7slzrHsYAAAAAAAAAAB3PFpgAAAAAAAAAAWk5ZssAAAAA0B7LuwSYvYgaN+E8Arqo0wGz3BN/4iq6RthlVjJtywrOtgjUEhrBJ95K8oeN8cp+ba4jakyiV+XQBWL/ynWoCg==
```

## Getting help

Please contact ahmet@evercoin.com
