#pragma once

#include <nn/types.h>

namespace nn {
namespace gfx {
struct MemoryPoolInfo;
template <typename T>
struct DeviceImpl;

namespace detail {
class MemoryPoolData {
public:
    void SetDefault();

    s32 _0;  // set to 0x88
    s32 _4;
    u64 _8;
};

template <typename T>
class MemoryPoolImpl {
public:
    MemoryPoolImpl();
    ~MemoryPoolImpl();

    void Initialize(nn::gfx::detail::DeviceImpl<
                        nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>>*,
                    nn::gfx::MemoryPoolInfo const&);
    void Finalize(nn::gfx::detail::DeviceImpl<
                  nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>>*);
    void* Map() const;
    void Unmap() const;
    void FlushMappedRange(s64, u64) const;
    void InvalidateMappedRange(s64, u64) const;

    u8 _0[0x120];  // pool data
};
};  // namespace detail
};  // namespace gfx
};  // namespace nn