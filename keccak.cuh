/*
 * keccak.cuh CUDA Implementation of BLAKE2B Hashing
 *
 * Date: 12 June 2019
 * Revision: 1
 *
 * This file is released into the Public Domain.
 */


#pragma once
#include "config.h"
#define KECCAK_ROUND 24
#define KECCAK_STATE_SIZE 25
#define KECCAK_Q_SIZE 192
void mcm_cuda_keccak_hash_batch(BYTE * in, WORD inlen, BYTE * out, WORD n_outbit, WORD n_batch, WORD n_iter=1);
