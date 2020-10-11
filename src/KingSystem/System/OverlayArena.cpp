#include "KingSystem/System/OverlayArena.h"
#include <heap/seadExpHeap.h>
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resUnit.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys {

OverlayArena::OverlayArena() {
    mUnits.initOffset(res::ResourceUnit::getArenaUnitListNodeOffset());
    mUnits2.initOffset(res::ResourceUnit::getArenaUnitListNode2Offset());
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

void OverlayArena::stubbed() {}

void OverlayArena::updateFlag8(bool on) {
    if (on != mFlags.isOn(Flag::_8) && mHeap)
        mFlags.change(Flag::_8, on);
}

void OverlayArena::clearUnits() {
    if (!mHeap)
        return;

    res::stubbedLogFunction();
    auto lock = sead::makeScopedLock(mCS);
    for (auto it = mUnits.robustBegin(), end = mUnits.robustEnd(); it != end; ++it) {
        res::ResourceUnit* unit = std::addressof(*it);
        res::stubbedLogFunction();
        res::ResourceMgrTask::instance()->deregisterUnit(unit);
        res::ResourceMgrTask::instance()->requestClearCacheForSync(&unit, true, false);
    }
    res::stubbedLogFunction();
}

bool OverlayArena::isFlag1Set() const {
    return mFlags.isOn(Flag::_1);
}

bool OverlayArena::hasNoUnits() const {
    return mUnits.isEmpty();
}

s32 OverlayArena::getNumUnits() const {
    return mUnits.size();
}

bool OverlayArena::isFlag10Set() const {
    return mFlags.isOn(Flag::_10);
}

bool OverlayArena::isFlag8Set() const {
    return mFlags.isOn(Flag::_8);
}

bool OverlayArena::checkIsOom() const {
    if (!mHeap)
        return false;

    const f32 used_size = mUsage1 + mUsage2;
    const size_t heap_size = mHeap->getSize();
    const f32 free_percentage =
        100.0f *
        std::max<f32>(1.0 - used_size / (heap_size - sead::ExpHeap::getManagementAreaSize(8)), 0);

    if (free_percentage < mMinFreePercentage) {
        if (res::returnFalse())
            res::stubbedLogFunction();

        setBloodyMoonReasonForOom_();
        return true;
    }

    return false;
}

// FIXME: figure out what sead function this is
bool seadCheckPointer(void* ptr);

// NON_MATCHING: branching
util::DualHeap* OverlayArena::makeDualHeap(u32 size, const sead::SafeString& name,
                                           sead::Heap::HeapDirection direction,
                                           res::ResourceUnit* unit, bool) {
    if (!mHeap)
        return nullptr;

    const auto alignment = res::getDefaultAlignment();
    const auto lock = sead::makeScopedLock(mCS);

    auto* heap = util::DualHeap::tryCreate(size, name, mHeap, mHeap2, alignment, direction, false);
    if (!heap) {
        if (res::returnFalse())
            res::stubbedLogFunction();

        if (!x_1(size))
            return nullptr;

        heap = util::DualHeap::tryCreate(size, name, mHeap, mHeap2, alignment, direction, false);
        if (!heap)
            return nullptr;
    }

    if (unit && !seadCheckPointer(unit)) {
        mUnits.pushBack(unit);
        mFlags.set(Flag::_2);
    }

    mFlags.set(Flag::_4);
    return heap;
}

void OverlayArena::addSize(s32 size) {
    mSize += size;
}

void OverlayArena::addSize2(s32 size) {
    mUsage1 += size;
}

}  // namespace ksys
