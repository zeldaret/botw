#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {

// FIXME: incomplete
class SoundResource {
    SEAD_SINGLETON_DISPOSER(SoundResource)
    SoundResource() = default;
    virtual ~SoundResource();

public:
    sead::Heap* getSoundDebugHeap() const { return mSoundDebugHeap; }

private:
    sead::Heap* mSoundResourceHeap;
    void* _30;
    sead::Heap* mSoundDebugHeap;
};
KSYS_CHECK_SIZE_NX150(SoundResource, 0x40);

}  // namespace ksys::snd
