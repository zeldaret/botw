/**
 * @file encryption.h
 * @brief NEX Encryption Algorithm.
 */

#pragma once

#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class Buffer;
class Key;

class EncryptionAlgorithm : public nn::nex::RootObject {
public:
    EncryptionAlgorithm(u32, u32);

    virtual ~EncryptionAlgorithm();

    virtual bool Encrypt(nn::nex::Buffer const&, nn::nex::Buffer*) = 0;
    virtual bool Encrypt(nn::nex::Buffer*);
    virtual bool Decrypt(nn::nex::Buffer const&, nn::nex::Buffer*) = 0;
    virtual bool Decrypt(nn::nex::Buffer*);
    virtual bool GetErrorString(u32, char* destStr, u64 errLen);
    virtual void KeyHasChanged();

    bool SetKey(nn::nex::Key const& key);

    u64 _8;
    u64 _10;
    u64 _18;
    u64 _20;
    u64 _28;
    u64 _30;
    u64 _38;
    u64 _40;
};

class RC4Encryption : public nn::nex::EncryptionAlgorithm {
public:
    RC4Encryption();

    virtual ~RC4Encryption();

    virtual bool Encrypt(nn::nex::Buffer const&, nn::nex::Buffer*);
    virtual bool Encrypt(nn::nex::Buffer*);
    virtual bool Decrypt(nn::nex::Buffer const&, nn::nex::Buffer*);
    virtual bool Decrypt(nn::nex::Buffer*);

    virtual void KeyHasChanged();

    void GetDefaultKey();
    void PrepareEncryption();
    void ReinitStateArray();
    void SetReinitEverytime(bool);

    u8 _48[0x298 - 0x48];
};
};  // namespace nex
};  // namespace nn