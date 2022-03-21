/**
 * @file AdvancedWaveSoundRuntime.h
 * @brief Runtime wave sound api.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace atk {
namespace detail {
class AdvancedWaveSoundRuntime {
public:
    AdvancedWaveSoundRuntime();
    ~AdvancedWaveSoundRuntime();

    void Initialize(s32, void**, void const*);
    void Finalize();
    s32 GetActiveCount() const;
    void SetupUserParam(void**, u64);
    void Update();

    u8 _0[0x30];
};
};  // namespace detail
};  // namespace atk
};  // namespace nn