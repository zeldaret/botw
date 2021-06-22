#include "KingSystem/Sound/sndResource.h"
#include <heap/seadDisposer.h>
#include <heap/seadExpHeap.h>
#include <heap/seadFrameHeap.h>

namespace ksys::snd {

SEAD_SINGLETON_DISPOSER_IMPL(SoundResource)

SoundResource::~SoundResource() {
    mSoundResourceHeap->destroy();
    _30->destroy();
    if (mSoundDebugHeap)
        mSoundDebugHeap->destroy();
}

void SoundResource::init(sead::Heap* heap, sead::Heap* debug_heap, bool extra_large) {
    mSoundResourceHeap =
        sead::FrameHeap::create(extra_large ? 0x9583000 : 0x6383000, "SoundResource", heap, 0x1000,
                                sead::FrameHeap::cHeapDirection_Forward, false);
    if (debug_heap)
        mSoundDebugHeap = sead::ExpHeap::create(0x1E00000u, "SoundDebug", debug_heap, 0x1000,
                                                sead::ExpHeap::cHeapDirection_Forward, false);
}

}  // namespace ksys::snd