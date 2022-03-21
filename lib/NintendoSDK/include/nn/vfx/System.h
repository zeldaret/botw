/**
 * @file System.h
 * @brief VFX system implementation.
 */

#pragma once

#include <nn/types.h>
#include <nn/vfx/Config.h>

// this class is massive
namespace nn {
namespace vfx {

struct Heap;

class System {
public:
    System(nn::vfx::Config const&);

    virtual ~System();
    virtual void Initialize(nn::vfx::Heap*, nn::vfx::Heap*, nn::vfx::Config const&);

    u8 _0[0x1700];
};
};  // namespace vfx
};  // namespace nn