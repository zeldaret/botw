/**
 * @file WaveSoundRuntime.h
 * @brief Wave sound runtime info.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace atk {
namespace detail {
class WaveSoundRuntime {
public:
    WaveSoundRuntime();
    ~WaveSoundRuntime();

    void Initialize(s32, void**, void const*);
    void Finalize();
    s32 GetActiveCount() const;
    s32 GetFreeWaveSoundCount() const;
    void SetupUserParam(void**, u64);
    void Update();

    u8 _0[0x80];
};
};  // namespace detail
};  // namespace atk
};  // namespace nn