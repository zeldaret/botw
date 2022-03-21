/**
 * @file hash.h
 * @brief NEX Hash Implementation.
 */

#pragma once

#include <nn/crypto.h>
#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class MD5 : public nn::crypto::detail::Md5Impl, public nn::nex::RootObject {
public:
    MD5();

    void init();
    void raw_digest(u8*);
    void hex_digest();

    u8 _5C[0x74 - 0x5C];
};

class Sha1 : public nn::crypto::detail::Sha1Impl, public nn::nex::RootObject {
public:
    Sha1();

    void Update(void const*, u64);
    void GetHash(void*, u64);
    void GenerateHash(void*, u64, void const*, u64);

    u32 _68;
};
};  // namespace nex
};  // namespace nn