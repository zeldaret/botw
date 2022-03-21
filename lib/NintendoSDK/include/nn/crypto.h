/**
 * @file crypto.h
 * @brief Crypto service implementation.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace crypto {
void GenerateSha256Hash(void*, ulong, void const*, ulong);

class Sha256Context;

void DecryptAes128Cbc(void*, u64, void const*, u64, void const*, u64, void const*, u64);
void EncryptAes128Cbc(void*, u64, void const*, u64, void const*, u64, void const*, u64);
void DecryptAes128Ccm(void*, u64, void*, u64, void const*, u64, void const*, u64, void const*, u64,
                      void const*, u64, u64);

namespace detail {
class Md5Impl {
public:
    void Initialize();
    void Update(void const*, u64 dataSize);
    void ProcessBlock();
    void GetHash(void*, u64 hashSize);
    void ProcessLastBlock();

    u32 _x0;
    u32 _x4;
    u32 _x8;
    u32 _xC;
    u8 _x10[0x50 - 0x10];
    u64 _x50;
    u32 _x58;
};

class Sha1Impl {
public:
    void Initialize();
    void Update(void const*, u64);
    void ProcessBlock(void const*);
    void GetHash(void* destHash, u64);
    void ProcessLastBlock();

    u64 _x0;
    u64 _x8;
    u32 _x10;
    u128 _x14;
    u128 _x24;
    u128 _x34;
    u32 _x44;
    u64 _x48;
    u64 _x50;
    u64 _x58;
    u64 _x60;
};

class Sha256Impl {
public:
    void Initialize();
    void Update(void const*, u64);
    void ProcessBlocks(u8 const*, u64);
    void GetHash(void* destHash, u64);
    void ProcessLastBlock();
    void InitializeWithContext(nn::crypto::Sha256Context const*);
    void GetContext(nn::crypto::Sha256Context*) const;

    u64 _x0;
    u64 _x8;
    u32 _x10;
    u128 _x14;
    u128 _x24;
    u128 _x34;
    u32 _x44;
    u64 _x48;
    u64 _x50;
    u64 _x58;
    u64 _x60;
    u64 _x68;
    u32 _x70;
};
};  // namespace detail
};  // namespace crypto
};  // namespace nn