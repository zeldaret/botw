/**
 * @file deviceimpl.h
 * @brief Device implementation for GFX.
 */

#pragma once

namespace nn {
namespace gfx {
class DeviceInfo;

namespace detail {
template <typename T>
class DeviceImpl {
public:
    DeviceImpl();
    ~DeviceImpl();

    void Initialize(nn::gfx::DeviceInfo const& deviceInfo);
    void Finalize();
};
};  // namespace detail
};  // namespace gfx
};  // namespace nn