// Copyright (c) 2009-2016 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Developers
// Copyright (c) 2015-2016 Silk Network Developers
// Copyright (c) 2015-2016 Ion Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdint.h>

// needed when linking transaction.cpp, since we are not going to pull real GetAdjustedTime from timedata.cpp
int64_t GetAdjustedTime()
{
    return 0;
}
