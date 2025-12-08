//encrypt private keys using aes
//I used tinyAES instead of OpenSSL due to the project's scope + difficulties configuring OpenSSL

#include "crypto.h"
#include "tinyaes/aes.h"
#include "tinyaes/aes.hpp"
#include <cstring>

std::vector<uint8_t> encrypt(const std::vector<uint8_t> &plain, 
const std::vector<uint8_t> &key, const std::vector<uint8_t> &iv) {
    std::vector<uint8_t> out = plain;
    AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key.data(), iv.data());
    AES_CBC_encrypt_buffer(&ctx, out.data(), out.size());
    return out;

}
std::vector<uint8_t> decrypt(const std::vector<uint8_t> &cipher, 
const std::vector<uint8_t> &key, const std::vector<uint8_t> &iv) {
    std::vector<uint8_t> out = cipher;
    AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key.data(), iv.data());
    AES_CBC_decrypt_buffer(&ctx, out.data(), out.size());
    return out;
};