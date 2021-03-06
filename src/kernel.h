// Copyright (c) 2012-2013 The PPCoin developers
// Copyright (c) 2015-2018 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_KERNEL_H
#define BITCOIN_KERNEL_H

#include "main.h"
#include "stakeinput.h"

// To decrease granularity of timestamp
// Supposed to be 2^n-1
static const int STAKE_TIMESTAMP_MASK = 15;

// MODIFIER_INTERVAL_RATIO:
// ratio of group interval length between the last group and the first group
static const int MODIFIER_INTERVAL_RATIO = 3;

// Compute the hash modifier for proof-of-stake
bool GetKernelStakeModifier(uint256 hashBlockFrom, uint64_t& nStakeModifier, int& nStakeModifierHeight, int64_t& nStakeModifierTime, bool fPrintProofOfStake);
bool ComputeNextStakeModifier(const CBlockIndex* pindexPrev, uint64_t& nStakeModifier, bool& fGeneratedStakeModifier);
uint256 ComputeStakeModifierV2(const CBlockIndex* pindexPrev, const uint256& kernel);

bool CheckStakeV2(CBlockIndex* pindexPrev, unsigned int nTxPrevTime, const COutPoint& prevout, unsigned int nTimeTx, int64_t nValueIn, const uint256& bnTarget, uint256& hashProofOfStake);
bool CheckStakeNewProtocol(const CDataStream& ssUniqueID, CAmount nValueIn, const uint64_t nStakeModifier, const uint256& bnTarget, unsigned int nTimeBlockFrom, unsigned int& nTimeTx, uint256& hashProofOfStake);
bool CheckStakeKernelHash(CStakeInput* stakeInput, unsigned int nBits, unsigned int nTimeBlockFrom, unsigned int& nTimeTx, uint256& hashProofOfStake);

// Check kernel hash target and coinstake signature
// Sets hashProofOfStake on success return
bool CheckProofOfStake(CBlockIndex* pindexPrev, const CBlock block, uint256& hashProofOfStake, std::unique_ptr<CStakeInput>& stake);
bool VerifySignature(const CTransaction& txFrom, const CTransaction& txTo, unsigned int nIn, unsigned int flags, int nHashType);

// Check whether the coinstake timestamp meets protocol
bool CheckCoinStakeTimestamp(int64_t nTimeBlock, int64_t nTimeTx);

// Get time weight using supplied timestamps
int64_t GetWeight(int64_t nIntervalBeginning, int64_t nIntervalEnd);

#endif // BITCOIN_KERNEL_H
