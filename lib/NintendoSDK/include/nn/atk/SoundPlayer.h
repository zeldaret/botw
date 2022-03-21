/**
 * @file SoundPlayer.h
 * @brief Sound player.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace atk {
enum PauseMode {

};

class SoundPlayer {
public:
    SoundPlayer();
    ~SoundPlayer();

    void StopAllSound(s32);
    void Update();
    void DoFreePlayerHeap();
    void detail_SortPriorityList(bool);
    void PauseAllSound(s32, bool);
    void PauseAllSound(bool, s32, nn::atk::PauseMode);
    void SetVolume(f32 vol);
    void SetLowPassFilterFrequency(f32 filterFreq);
    void SetBiquadFilter(s32 filterType, f32 baseFreq);
    void SetDefaultOutputLine(u32 line);

    void detail_SetPlayableSoundLimit(s32 limit);
    bool CanPlaySound(s32);

    u64 _0;
    u64 _8;
    u64 _10;
    u64 _18;
    u64 _20;
    u64 _28;
    u64 _30;
    u64 _38;
    s32 _40;
    s32 mPlayableSoundCount;  // _44
    s32 _48;
    f32 mVolume;             // _4C
    f32 mLowPassFreq;        // _50
    s32 mFilterType;         // _54
    f32 mBaseFreq;           // _58
    u32 mDefaultOutputLine;  // _5C
    f32 mOutputVolume;       // _60
    u64 _64;
    u64 _6C;
};
};  // namespace atk
};  // namespace nn