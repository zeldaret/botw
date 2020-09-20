#include "KingSystem/System/OverlayArena.h"
#include <heap/seadExpHeap.h>
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys {

OverlayArena::OverlayArena() {
    // FIXME: these should use offsetof()
    mUnits.initOffset(0xc0);
    mOffsetList2.initOffset(0xd0);
}

OverlayArena::~OverlayArena() {
    destroy();
}

// NON_MATCHING: branching at the end (csel instead of a branch)
bool OverlayArena::init(const OverlayArena::InitArg& arg) {
    if (!arg.heap) {
        res::stubbedLogFunction();
        return false;
    }

    if (arg.size == 0)
        res::stubbedLogFunction();

    mFlags.change(Flag::_1, arg.set_flag_1);

    mHeap = sead::ExpHeap::create(arg.size, arg.name, arg.heap, arg.alignment,
                                  sead::Heap::cHeapDirection_Forward, true);

    if (arg.use_best_fit_alloc_mode)
        mHeap->setAllocMode(sead::ExpHeap::AllocMode::BestFit);

    mHeapSize = mHeap->getSize();
    _cc = 0;
    mHeapFreeSize = mHeap->getFreeSize();
    mHeapName = mHeap->getName();
    mUsagePercentage = 0.0;
    _c8 = 0;
    mMinFreePercentage = arg.min_free_percentage;

    if (res::ResourceMgrTask::instance())
        res::ResourceMgrTask::instance()->insertOverlayArena(this);

    mFlags.change(Flag::_20, arg.set_flag_20);
    mFlags.change(Flag::_10, arg.set_flag_10);

    struct UnusedTemp {
        sead::SafeString str;
        void* _10 = nullptr;
    };
    [[maybe_unused]] UnusedTemp temp;
    temp.str = arg.name;

    mFlags.change(Flag::_8, arg.set_flag_8);

    return true;
}

}  // namespace ksys
