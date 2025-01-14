/*
 * sha1.cuh CUDA Implementation of SHA1 Hashing    
 *
 * Date: 12 June 2019
 * Revision: 1
 * 
 * Based on the public domain Reference Implementation in C, by
 * Brad Conte, original code here:
 *
 * https://github.com/B-Con/crypto-algorithms
 *
 * This file is released into the Public Domain.
 */

 
#pragma once
#include "config.h"
#define SHA1_BLOCK_SIZE 20     
void mcm_cuda_sha1_hash_batch(BYTE* in, WORD inlen, BYTE* out, WORD n_batch, WORD n_iter=1);
