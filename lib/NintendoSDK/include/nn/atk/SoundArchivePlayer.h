/**
 * @file SoundArchivePlayer.h
 * @brief Basic sound player from a sound archive.
 */

#pragma once

#include <nn/atk/detail/AdvancedWaveSoundRuntime.h>
#include <nn/atk/detail/SequenceSoundRuntime.h>
#include <nn/atk/detail/SoundArchiveManager.h>
#include <nn/atk/detail/StreamSoundRuntime.h>
#include <nn/atk/detail/WaveSoundRuntime.h>

namespace nn {
namespace atk {
class SoundArchivePlayer {
public:
    SoundArchivePlayer();

    virtual ~SoundArchivePlayer();

    bool IsAvailable() const;
    void Finalize();
    void StopAllSound(s32, bool);
    void DisposeInstances();

    nn::atk::detail::SoundArchiveManager mArchiveManager;          // _8
    nn::atk::detail::SequenceSoundRuntime mSeqSoundRuntime;        // _50
    nn::atk::detail::WaveSoundRuntime mWaveSoundRuntime;           // _130
    nn::atk::detail::AdvancedWaveSoundRuntime mAdvancedWaveSound;  // _1B0
    nn::atk::detail::StreamSoundRuntime mStreamSoundRuntime;       // _1E0
    u64 _290;
    u32 _298;
    u8 _29C[0x2E8 - 0x29C];
};
};  // namespace atk
};  // namespace nn