/**
 * @file key.h
 * @brief NEX Key Implementation.
 */

#pragma once

#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class String;

class Key : public nn::nex::RootObject {
public:
    Key();
    Key(u8 const* src, u64 size);
    Key(u64 size);
    Key(nn::nex::Key const&);
    Key(nn::nex::String const&);

    virtual ~Key();

    u64* GetContentPtr();
    u64 GetLength() const;
    nn::nex::Key& operator=(nn::nex::Key const&);
    bool operator==(nn::nex::Key const&);
    bool operator!=(nn::nex::Key const&);
    void PrepareContentPtr(u64);
    nn::nex::String* ToString();
    void ExtractToString(nn::nex::String*) const;
    void Trace(u64) const;
    void GenerateRandomKey(u64);

    u64* mContentPtrStart;  // _10
    u64* mContentPtrEnd;    // _18
};
};  // namespace nex
};  // namespace nn