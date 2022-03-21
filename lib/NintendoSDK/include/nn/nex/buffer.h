/**
 * @file buffer.h
 * @brief NEX buffer implementation.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace nex {
class String;
// todo
class Buffer {
public:
    Buffer(nn::nex::Buffer const&);
    Buffer(nn::nex::Buffer&&);
    Buffer(nn::nex::String const&);

    void FreeDataBuffer(u8*, u64);

    virtual ~Buffer();
};
};  // namespace nex
};  // namespace nn