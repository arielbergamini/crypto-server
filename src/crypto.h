#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdint>

//get my super secret key from env
std::vector<uint8_t> getEnvKey() {
    const char* env = std::getenv("TOTALLY_DEFINITELY_CERTAINLY_NOT_MY_KEY");
    if (!env) {
        throw std::runtime_error("env var TOTALLY_DEFINITELy_CERTAINLY_NOT_MY_KEY not set");
    }

    std::string keyStr(env);
    std::vector<uint8_t> key(32, 0); //pad w 0s bc aes 256 needs 32bytes
    for (size_t i=0; i<keyStr.size() && i<32; i++) {
        key[i] = static_cast<uint8_t>(keyStr[i]);
    }

    return key;
}

//encrypt raw key
std::vector<uint8_t> encrypt(const std::vector<uint8_t> &plain, 
    const std::vector<uint8_t> &key, const std::vector<uint8_t> &iv);

//decrypt ciphertext
std::vector<uint8_t> decrypt(const std::vector<uint8_t> &cipher, 
    const std::vector<uint8_t> &key, const std::vector<uint8_t> &iv);