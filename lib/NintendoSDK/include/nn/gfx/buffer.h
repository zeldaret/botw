/**
 * @file buffer.h
 * @brief GFX Buffers.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace gfx {
class BufferInfo {
public:
    void SetDefault();

    u64 mInfo;  // _0
};

class BufferTextureViewInfo {
public:
    void SetDefault();

    u64 _0;
    u64 _8;
    u64 _10;
};
};  // namespace gfx
};  // namespace nn