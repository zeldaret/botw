/**
 * @file TexCoordArray.h
 * @brief Texture coordinate array implementation.
 */

#pragma once

#include <nn/types.h>

namespace nn {

namespace util {
struct Float2;
}

namespace ui2d {
class Layout;

namespace detail {
class TexCoordArray {
public:
    void Initialize();
    void Free();
    void Reserve(s32);
    void SetSize(s32 size);
    void GetCoord(nn::util::Float2*, s32) const;
    void SetCoord(s32, nn::util::Float2 const*);
    void Copy(void const*, s32);
    bool CompareCopiedInstanceTest(nn::ui2d::detail::TexCoordArray const&) const;

    u16 _0;
    u16 _2;
    u32 _4;                     // padding?
    nn::ui2d::Layout* mLayout;  // _8
};
};  // namespace detail
};  // namespace ui2d
};  // namespace nn