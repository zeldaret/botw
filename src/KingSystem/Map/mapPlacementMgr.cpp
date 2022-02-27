#include "KingSystem/Map/mapPlacementMgr.h"
#include <thread/seadThreadUtil.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actClusteredRenderer.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementTree.h"
#include "KingSystem/System/VFR.h"

namespace ksys::map {

SEAD_SINGLETON_DISPOSER_IMPL(PlacementMgr)

PlacementMgr::PlacementMgr() : mThreadParams(this, &PlacementMgr::threadFn) {}

PlacementMgr::~PlacementMgr() {
    mThreadHeap->destroy();
    mDynamicHeap->destroy();
    mVillagerHeap->destroy();
    mTraverseResultHeap->destroy();
}

void PlacementMgr::releaseTree() {
    if (mPlacementTree != nullptr)
        delete mPlacementTree;
    mPlacementTree = nullptr;
}

// NON_MATCHING
void PlacementMgr::x_3() {
    auto ac = act::ActorCreator::instance();
    const auto loc = sead::makeScopedLock(ac->getCS());
    if (mNumStaticObjs < mPlacementActors->getNumStaticObjs()) {
        auto list = ac->getActorList();
        for (act::Actor& node : list) {
            if (node.getMapObject() == mPlacementActors->getStaticObj_2(mNumStaticObjs)) {
                node.deleteLater(act::BaseProc::DeleteReason::_0);
            }
        }
    }
}

void PlacementMgr::reset7F0() {
    _7f0 = 0;
}

// NON_MATCHING
void PlacementMgr::initClusteredRenderer() {
    if (mThread != nullptr && mClusteredRenderer == nullptr)
        return;
    if (mThreadHeap == nullptr)
        return;

    mFlags.reset(MgrFlag::_40000);
    mThread = new (mThreadHeap)
        sead::DelegateThread("PlacementMgr", &mThreadParams, mThreadHeap,
                             sead::ThreadUtil::ConvertPrioritySeadToPlatform(0x14),
                             sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0x100000, 0x20);
    mRequestedMsg = 0;
    sead::CoreIdMask mask{sead::CoreId::cSub4};
    mThread->setAffinity(mask);
    mThread->start();
    mFlags.reset(MgrFlag::_2);

    if (mClusteredRenderer != nullptr) {
        mClusteredRenderer->startThread();
    }
}

void PlacementMgr::auto0() {
    if (mThread == nullptr)
        return;
    mFlags.set(MgrFlag::_2);
    _278 = 0;
}

void PlacementMgr::printDebugInfo() {
    if (!sFlags.isOn(MgrStaticFlags::debug))
        return;

    // Actor info:%d (loaded:%d) Instance:%d
    sead::FormatFixedSafeString<128> s1("アクタ情報:%d（ロード済み:%d) インスタンス:%d",
                                        mPlacementActors->mActorDataMapSize, mLoadedActorCount,
                                        mPlacementActors->getNumStaticObjs());
    // Traverse result pre-actor:%d actor:%d
    sead::FormatFixedSafeString<128> s2("トラバース結果  pre-actor:%d actor:%d",
                                        mTraverseResults[mTraverseResultIdx].pre_actors.size(),
                                        mTraverseResults[mTraverseResultIdx].actors.size());
    // Memory preActor:%dk info:%dk result:%dk mass:%dk clustered:%d
    sead::FormatFixedSafeString<128> s3(
        "メモリ preActor:%dk info:%dk result:%dk mass:%dk clustered:%dk", 40468, 2437, 87,
        mMassMemoryUsage / 1024, mClusteredMemoryUsage / 1024);
    // Dynamic heap remaining:%dk
    sead::FormatFixedSafeString<128> s4("動的ヒープ残り:%dk",
                                        u32(mDynamicHeap->getFreeSize() / 1024));
}

void PlacementMgr::incrementCounter() {
    _278++;
}

void PlacementMgr::x() {
    if (mFlags.isOn(MgrFlag::_2))
        return;

    mPlacementActors->x_9();
    mIntTime++;

    f32 last_time = mTime;
    auto* vfr = VFR::instance();
    mTime += vfr->getDeltaTime();
    mTimeUpdated = s32(last_time) != s32(mTime);
}

void PlacementMgr::auto5() {
    mFlags.set(MgrFlag::_1);
}

void PlacementMgr::auto16() {
    mFlags.set(MgrFlag::_100000);
    mFlags.set(MgrFlag::_200000);
    mFlags.set(MgrFlag::_400000);
}

bool PlacementMgr::someFlagCheck() const {
    if (mFlags.isOn(MgrFlag::_80000))
        return true;
    return mFlags.isOn(MgrFlag::_100000);
}

}  // namespace ksys::map
