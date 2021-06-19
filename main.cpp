#include <string>
#include <iostream>
#include <chrono>
#include <cstring>
#include <iomanip>
#include "chrono.hpp"
#include "common.hpp"





int main(){
    size_t input_block_size = 512 * 1024; //bytes
    size_t n_blocs = 1024 * 4;
    size_t n_iters = 20;

    run_benchmark<hash::method::keccak, 128>(input_block_size, n_blocs, n_iters);
    run_benchmark<hash::method::blake2b, 128>(input_block_size, n_blocs, n_iters);
    run_benchmark<hash::method::md5>(input_block_size, n_blocs, n_iters);
    run_benchmark<hash::method::sha1>(input_block_size, n_blocs, n_iters);
    run_benchmark<hash::method::sha256>(input_block_size, n_blocs, n_iters);
    run_benchmark<hash::method::md2>(input_block_size, n_blocs, n_iters);
    
}