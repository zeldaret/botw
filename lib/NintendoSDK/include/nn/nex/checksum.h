/**
 * @file checksum.h
 * @brief NEX Checksum Implementation.
 */

#pragma once

#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class Buffer;

class ChecksumAlgorithm : public nn::nex::RootObject {
public:
    ChecksumAlgorithm();

    virtual ~ChecksumAlgorithm();

    virtual bool ComputeChecksum(nn::nex::Buffer const&, nn::nex::Buffer*) = 0;
    // virtual bool ComputeChecksum(u8 const **, u64 const *, u64, nn::nex::SignatureBytes &) = 0;
    virtual bool IsReady() const;
    virtual void ComputeChecksumForTransport(u8 const*, u64);
    virtual u32 ComputeChecksumForTransportArray(u8 const**, u64 const*, u64) = 0;
    virtual u32 GetChecksumLength() = 0;

    u64 _8;
    u8 _10;
};

class MD5Checksum : public nn::nex::ChecksumAlgorithm {
public:
    MD5Checksum();

    virtual ~MD5Checksum();

    virtual bool ComputeChecksum(nn::nex::Buffer const&, nn::nex::Buffer*);
    virtual u32 ComputeChecksumForTransportArray(u8 const**, u64 const*, u64);
    virtual u32 GetChecksumLength();
};

class CRC16Checksum : public nn::nex::ChecksumAlgorithm {
public:
    CRC16Checksum();

    virtual ~CRC16Checksum();

    virtual bool ComputeChecksum(nn::nex::Buffer const&, nn::nex::Buffer*);
    virtual u32 ComputeChecksumForTransportArray(u8 const**, u64 const*, u64);
    virtual u32 GetChecksumLength();
};

/*
this actually inherits some sort of KeyedChecksum thing. whatever
class HMACChecksum : public nn::nex::ChecksumAlgorithm
{

};
*/
};  // namespace nex
};  // namespace nn