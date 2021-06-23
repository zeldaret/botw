#pragma once

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

}  // namespace ksys::snd
