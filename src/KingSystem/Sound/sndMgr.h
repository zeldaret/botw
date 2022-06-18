#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace ksys::snd {

enum class AudioChannelType {
    Mono = 1,
    Stereo = 2,
    _5_1ch = 6,
    Other = -1  // TODO: does Other have a definite value?
};

// FIXME: incomplete
struct SoundMgr {
    SEAD_SINGLETON_DISPOSER(SoundMgr);

    virtual ~SoundMgr();

public:
    u8 _0[0x248];
    AudioChannelType mAudioChannelType;
};

}  // namespace ksys::snd