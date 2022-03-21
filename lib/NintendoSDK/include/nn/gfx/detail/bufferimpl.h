/**
 * @file bufferimpl.h
 * @brief Buffer implementation for GFX.
 */

#pragma once

namespace nn {
namespace gfx {
class GpuAddress;
class BufferInfo;

namespace detail {
template <typename T>
class MemoryPoolImpl;
template <typename T>
class DeviceImpl;

template <typename T>
class BufferImpl {
public:
    BufferImpl();
    ~BufferImpl();

    void Initialize(nn::gfx::detail::DeviceImpl<
                        nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>>*,
                    nn::gfx::BufferInfo const&,
                    nn::gfx::detail::MemoryPoolImpl<
                        nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>>*,
                    s64, u64);
    void Finalize(nn::gfx::detail::DeviceImpl<
                  nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>>*);
    void* Map() const;
    void Unmap() const;
    void FlushMappedRange(s64, u64) const;
    void InvalidateMappedRange(s64, u64) const;
    void GetGpuAddress(nn::gfx::GpuAddress*) const;

    T* mBuff;  // _0
};

template <typename T>
class CommandBufferImpl {
public:
    CommandBufferImpl();
    ~CommandBufferImpl();

    void Reset();
    void Begin();
    void End();
    void Dispatch(s32, s32, s32);
};
};  // namespace detail
};  // namespace gfx
};  // namespace nn