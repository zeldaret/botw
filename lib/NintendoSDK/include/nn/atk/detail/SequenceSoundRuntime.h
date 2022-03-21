/**
 * @file SequenceSoundRuntime.h
 * @brief Sequenced Sound Runtime Info
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace atk {
namespace detail {
class SoundArchiveManager;

class SequenceSoundRuntime {
public:
    SequenceSoundRuntime();
    ~SequenceSoundRuntime();

    void Initialize(s32, void**, void const*);
    void Finalize();
    void SetupSequenceTrack(s32, void**, void const*);
    void SetupUserParam(void**, u64);
    bool IsSoundArchiveAvailable() const;
    s32 GetActiveCount() const;
    s32 GetFreeCount() const;
    void SetSequenceSkipIntervalTick(s32 tick);
    s32 GetSequenceSkipIntervalTick();
    void Update();

    u8 _0[0xD0];
    nn::atk::detail::SoundArchiveManager* mArchiveManager;  // _D0
    u64 _D8;
};
};  // namespace detail
};  // namespace atk
};  // namespace nn