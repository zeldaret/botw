/**
 * @file ResMaterial.h
 * @brief Resource material for models.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace g3d {
typedef void* TextureRef;

class ResMaterial {
public:
    u64 BindTexture(nn::g3d::TextureRef (*)(char const*, void*), void*);
    void ForceBindTexture(nn::g3d::TextureRef const&, char const*);
    void ReleaseTexture();
    void
    Setup(nn::gfx::TDevice<nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<4>>>*);
    void
    Cleanup(nn::gfx::TDevice<nn::gfx::ApiVariation<nn::gfx::ApiType<8>, nn::gfx::ApiVersion<8>>>*);
    void Reset();
    void Reset(u32);

    u8 _0[0xB4];
};
};  // namespace g3d
};  // namespace nn