// Copyright (c) 2009-2016 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Developers
// Copyright (c) 2015-2016 Silk Network Developers
// Copyright (c) 2015-2016 Ion Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ION_SCRIPT_SIGN_H
#define ION_SCRIPT_SIGN_H

#include "script/interpreter.h"
#include "script/standard.h"

class CKeyStore;
class CScript;
class CTransaction;

struct CMutableTransaction;

bool VerifySignature(const CTransaction& txFrom, const CTransaction& txTo, unsigned int nIn, unsigned int flags, int nHashType);

bool Solver(const CKeyStore& keystore, const CScript& scriptPubKey, uint256 hash, int nHashType,
                  CScript& scriptSigRet, txnouttype& whichTypeRet);
bool SignSignature(const CKeyStore& keystore, const CScript& fromPubKey, CMutableTransaction& txTo, unsigned int nIn, int nHashType=SIGHASH_ALL);
bool SignSignature(const CKeyStore& keystore, const CTransaction& txFrom, CMutableTransaction& txTo, unsigned int nIn, int nHashType=SIGHASH_ALL);

/**
 * Given two sets of signatures for scriptPubKey, possibly with OP_0 placeholders,
 * combine them intelligently and return the result.
 */
CScript CombineSignatures(const CScript& scriptPubKey, const CTransaction& txTo, unsigned int nIn, const CScript& scriptSig1, const CScript& scriptSig2);

#endif // ION_SCRIPT_SIGN_H
