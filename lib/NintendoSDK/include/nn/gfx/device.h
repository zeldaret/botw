/**
 * @file device.h
 * @brief Device implementation for GFX.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace gfx {
class DeviceInfo {
public:
    u64 mInfo;  // _0
};

template <typename T>
class TDevice {};
};  // namespace gfx
};  // namespace nn