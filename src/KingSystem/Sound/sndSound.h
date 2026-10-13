#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {

class SoundResource {
    SEAD_SINGLETON_DISPOSER(SoundResource)
    SoundResource() = default;
    virtual ~SoundResource();

public:
    void init(sead::Heap* heap, sead::Heap* debug_heap, bool extra_large);
    sead::Heap* getSoundDebugHeap() const { return mSoundDebugHeap; }

private:
    sead::Heap* mSoundResourceHeap = nullptr;
    sead::Heap* _30 = nullptr;  // TODO find out what this does
    sead::Heap* mSoundDebugHeap = nullptr;
};
KSYS_CHECK_SIZE_NX150(SoundResource, 0x40);

enum class AudioChannelType {
    Mono = 1,
    Stereo = 2,
    _5_1ch = 6,
    Other = -1  // TODO: does Other have a definite value?
};

// FIXME: incomplete
struct SoundMgr {
    SEAD_SINGLETON_DISPOSER(SoundMgr)

    virtual ~SoundMgr();

public:
    u8 _28[0x248];
    AudioChannelType mAudioChannelType;
};

}  // namespace ksys::snd
