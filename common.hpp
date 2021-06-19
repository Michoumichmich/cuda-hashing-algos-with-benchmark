#include "blake2b.cuh"
#include "keccak.cuh"
#include "md2.cuh"
#include "md5.cuh"
#include "sha1.cuh"
#include "sha256.cuh"

namespace hash{
enum class method { sha256, keccak, blake2b, sha1, md5, md2 };

template <method M, int n_outbit = 0> static int get_block_size() {
  if constexpr (M == method::sha256) {
    return SHA256_BLOCK_SIZE;
  } else if (M == method::md5) {
    return MD5_BLOCK_SIZE;
  } else if (M == method::md2) {
    return MD2_BLOCK_SIZE;
  } else if (M == method::sha1) {
    return SHA1_BLOCK_SIZE;
  } else if (M == method::keccak) {
    return n_outbit >> 3;
  } else if (M == method::blake2b) {
    return n_outbit >> 3;
  }
}

template <method M, int n_outbit = 0> static std::string get_name() {
  if constexpr (M == method::sha256) {
    return std::string("sha256");
  } else if (M == method::md5) {
    return std::string("md5");
  } else if (M == method::md2) {
    return std::string("md2");
  } else if (M == method::sha1) {
    return std::string("sha1");
  } else if (M == method::keccak) {
    return std::string("keccak");
  } else if (M == method::blake2b) {
    return std::string("blake2b");
  }
}

template <method M, int n_outbit =0>
void compute(BYTE *indata, WORD inlen, BYTE *outdata, WORD n_batch,
                          WORD n_iter, BYTE *key = nullptr,
                          WORD keylen = 0) {
  if constexpr (M == method::sha256) {
     mcm_cuda_sha256_hash_batch(indata, inlen, outdata, n_batch, n_iter);
  } else if (M == method::md5) {
     mcm_cuda_md5_hash_batch(indata, inlen, outdata, n_batch, n_iter);
  } else if (M == method::md2) {
     mcm_cuda_md2_hash_batch(indata, inlen, outdata, n_batch, n_iter);
  } else if (M == method::sha1) {
     mcm_cuda_sha1_hash_batch(indata, inlen, outdata, n_batch, n_iter);
  } else if (M == method::keccak) {
     mcm_cuda_keccak_hash_batch(indata, inlen, outdata, n_outbit, n_batch, n_iter);
  } else if (M == method::blake2b) {
     mcm_cuda_blake2b_hash_batch(key, keylen, indata, inlen, outdata, n_outbit, n_batch, n_iter);
  }
}

}

template<hash::method M, int ... args>
void run_benchmark(size_t input_block_size, size_t n_blocs, size_t n_iters) {
    std::cout << std::endl << "Running " << hash::get_name<M, args...>();
    auto out_block_size = hash::get_block_size<M, args...>();

    auto all_input_data = (BYTE*) malloc(input_block_size * n_blocs);
    auto all_output_hashes = (BYTE*) malloc(out_block_size * n_blocs);
    //fill_rand<BYTE>(all_input_data.get(), all_input_data.alloc_count());
    BYTE key[64];
    std::memset(key, 1, 64);

    Chrono c("All iterations");
    hash::compute<M, args...>(all_input_data, input_block_size, all_output_hashes, n_blocs, n_iters, key, 64);
   
    std::cout << std::endl << "GB hashed per sec: " << (double) n_iters / c.stop() * (double) (input_block_size * n_blocs) / 1e9 << std::endl;
    std::cout << "Hash Rate: " << (double) n_iters / c.stop() * (double) (input_block_size * n_blocs / out_block_size) / 1e6 << " Mh/s" << std::endl;
    
    std::cout << "Res: ";
    for (int i = 0; i < out_block_size; ++i) // only the first bloc
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int) (all_output_hashes[i]) << " ";
    std::cout << std::dec << std::endl;

    free(all_input_data);
    free(all_output_hashes);
}
