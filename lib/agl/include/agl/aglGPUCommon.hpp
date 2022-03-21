#pragma once

#include <basis/seadTypes.h>

namespace agl {
enum class MemoryAttribute : u32 {
    Default = 0,
    _00 = 1 << 0,
    _01 = 1 << 1,
    CompressibleMemory = 1 << 2,
    CpuCached = 1 << 3,
    _04 = 1 << 4,
    // PHYSICAL, no CPU and GPU access.
    MemoryReserved = 1 << 7,
    GpuCached = 1 << 8,

    // TODO: More?
};

struct GPUMemVoidAddr {
    // FIXME: what are thoses?
    u64 _0;
    u64 _8;
    u64 mAddress;

    u64 getGPUMemBlock() const { return mAddress; }
};

}  // namespace agl