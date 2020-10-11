#include "KingSystem/System/OverlayArenaSystem.h"
#include <KingSystem/Resource/resResourceMgrTask.h>
#include <heap/seadExpHeap.h>
#include <heap/seadHeap.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Sound/sndResource.h"
#include "KingSystem/System/OverlayArena.h"
#include "KingSystem/System/SystemPauseMgr.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(OverlayArenaSystem)

OverlayArenaSystem::OverlayArenaSystem()
    : mEvent(nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified, true) {
    mEvent.resetSignal();
}

OverlayArenaSystem::~OverlayArenaSystem() {
    destroyHeaps();

    if (mSzsDecompressorInstHeap)
        mSzsDecompressorInstHeap->destroy();

    if (mTask)
        delete mTask;
    mTask = nullptr;

    if (mPrepareThread) {
        mPrepareThread->quitAndWaitDoneSingleThread(false);
        if (mPrepareThread)
            delete mPrepareThread;
        mPrepareThread = nullptr;
    }
}

void OverlayArenaSystem::destroyHeaps() {
    res::stubbedLogFunction();
    if (mGameDataWorkHeap) {
        mGameDataWorkHeap->destroy();
        mGameDataWorkHeap = nullptr;
    }
    res::stubbedLogFunction();

    res::stubbedLogFunction();
    if (mFixedHeap) {
        mFixedHeap->destroy();
        mFixedHeap = nullptr;
    }
    res::stubbedLogFunction();

    res::stubbedLogFunction();
    if (mMovableMemoryHeap) {
        mMovableMemoryHeap->destroy();
        mMovableMemoryHeap = nullptr;
    }
    res::stubbedLogFunction();

    mFlags.set(Flag::_2);
}

// NON_MATCHING: reordering for TaskThread::InitArg
bool OverlayArenaSystem::init(const InitArg& arg, sead::Heap* heap) {
    mSystemPauseMgr = arg.system_pause_mgr;

    mPrepareThread = new (heap) util::TaskThread(
        "OverlayArena Prepare", heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(17),
        sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0x14000, 32);

    {
        util::TaskThread::InitArg arg_;
        arg_.batch_size = 0;
        arg_.queue = nullptr;
        arg_.num_lanes = 1;
        arg_.heap = heap;
        mPrepareThread->init(arg_);
        mPrepareThread->setAffinity(sead::CoreIdMask(sead::CoreId::cMain));
        mPrepareThread->start();
    }

    mDelegate = {this, &OverlayArenaSystem::delegatedFunction};

    {
        mTask = new (heap) util::Task(heap);
        util::TaskDelegateSetter setter;
        mTask->setDelegate(setter);
    }

    {
        OverlayArenaSystemS2::InitArg arg_;
        arg_.s1 = &mS1;
        arg_.system_pause_mgr = mSystemPauseMgr;
        mS2.init(arg_);
    }

    mSzsDecompressorInstHeap = sead::ExpHeap::create(
        sead::ExpHeap::getManagementAreaSize(8) + 0x1e20, "SZSDecompressorInst", heap,
        sizeof(void*), sead::Heap::cHeapDirection_Forward, true);

    if (heap) {
        mFlags.reset(Flag::_2);
        mFixedHeap = sead::ExpHeap::tryCreate(0x17600000, "FixedHeap", heap, sizeof(void*),
                                              sead::Heap::cHeapDirection_Forward, false);
        if (mFixedHeap) {
            createHeaps();
            mMovableMemoryHeap =
                sead::ExpHeap::tryCreate(0x100000, "MovableMemoryHeap", heap, sizeof(void*),
                                         sead::Heap::cHeapDirection_Forward, false);
        }
    }

    res::stubbedLogFunction();
    mS1.init();
    res::stubbedLogFunction();

    if (mSystemPauseMgr) {
        res::stubbedLogFunction();
        mSystemPauseMgr->m2();
        res::stubbedLogFunction();
    }

    return true;
}

void OverlayArenaSystem::getSzsDecompressor(sead::SZSDecompressor** decompressor) const {
    if (decompressor)
        *decompressor = mSzsDecompressor;
}

OverlayArena* OverlayArenaSystem::getArena() const {
    return mArena;
}

OverlayArena* OverlayArenaSystem::getTeraSzsWorkArena() const {
    return mTeraSzsWorkArena;
}

OverlayArena* OverlayArenaSystem::getAudioArena() const {
    return mAudioArena;
}

OverlayArena* OverlayArenaSystem::getUnknownArena() const {
    return mUnknownArena;
}

void OverlayArenaSystem::createHeaps() {
    res::stubbedLogFunction();

    res::stubbedLogFunction();
    mGameDataWorkHeap =
        sead::ExpHeap::tryCreate(0x400000, "GameDataWork", mFixedHeap, sizeof(void*),
                                 sead::Heap::cHeapDirection_Forward, true);
    if (!mGameDataWorkHeap)
        return;

    res::stubbedLogFunction();

    createSzsDecompressor();
    createTexArcWorkHeap();
    createArena();
    createTeraSzsWorkArena();
    createAudioArena();
    createJpegHeap();
    createTeraWorkHeap();
    createPlacementTreeHeap();

    res::stubbedLogFunction();
}

void OverlayArenaSystem::createTexArcWorkHeap() {
    res::stubbedLogFunction();

    if (mTexArcWorkHeap)
        return;

    if (!mFixedHeap)
        return;

    mTexArcWorkHeap = sead::ExpHeap::tryCreate(0xc000000, "TexArcWork", mFixedHeap, sizeof(void*),
                                               sead::Heap::cHeapDirection_Forward, true);
    if (mTexArcWorkHeap)
        res::stubbedLogFunction();
}

void OverlayArenaSystem::createArena() {
    res::stubbedLogFunction();

    if (mArena)
        return;

    if (!mFixedHeap)
        return;

    mArena = new (mFixedHeap, std::nothrow) OverlayArena;
    if (!mArena) {
        mArena = nullptr;
        return;
    }

    OverlayArena::InitArg arg;
    arg.size = 0x3affee0;
    arg.set_flag_1 = true;
    arg.set_flag_8 = true;
    arg.use_best_fit_alloc_mode = false;
    arg.name = "ForOverlayArena";
    arg.heap = mFixedHeap;
    arg.heap2 = nullptr;
    arg._6 = false;
    arg.set_flag_10 = false;
    if (mArena->init(arg))
        res::stubbedLogFunction();
}

void OverlayArenaSystem::createTeraSzsWorkArena() {
    res::stubbedLogFunction();

    if (mTeraSzsWorkArena)
        return;

    if (!mFixedHeap)
        return;

    mTeraSzsWorkArena = new (mFixedHeap, std::nothrow) OverlayArena;
    if (!mTeraSzsWorkArena) {
        mTeraSzsWorkArena = nullptr;
        return;
    }

    OverlayArena::InitArg arg;
    arg.size = 0x9ffee0;
    arg.set_flag_1 = true;
    arg.set_flag_8 = true;
    arg.use_best_fit_alloc_mode = false;
    arg.name = "TeraSZSWork";
    arg.heap = mFixedHeap;
    arg.heap2 = nullptr;
    arg._6 = false;
    arg.set_flag_10 = false;
    if (mTeraSzsWorkArena->init(arg))
        res::stubbedLogFunction();
}

void OverlayArenaSystem::createAudioArena() {
    res::stubbedLogFunction();

    if (mAudioArena)
        return;

    if (!mFixedHeap)
        return;

    mAudioArena = new (mFixedHeap, std::nothrow) OverlayArena;
    if (!mAudioArena) {
        mAudioArena = nullptr;
        return;
    }

    OverlayArena::InitArg arg;
    arg.size = 0x2e00000;
    arg.set_flag_8 = true;
    arg.use_best_fit_alloc_mode = false;
    arg.name = "Audio(OverlayArena)";
    arg.heap = mFixedHeap;
    arg.heap2 = snd::SoundResource::instance()->getSoundDebugHeap();
    arg.alignment = 0x1000;
    if (mAudioArena->init(arg))
        res::stubbedLogFunction();
}

void OverlayArenaSystem::createJpegHeap() {
    res::stubbedLogFunction();

    if (mJpegHeap)
        return;

    if (!mFixedHeap)
        return;

    mJpegHeap = sead::ExpHeap::tryCreate(0x900000, "JPEG", mFixedHeap, sizeof(void*),
                                         sead::Heap::cHeapDirection_Forward, true);
    if (mJpegHeap)
        res::stubbedLogFunction();
}

void OverlayArenaSystem::createTeraWorkHeap() {
    res::stubbedLogFunction();

    if (tera::System::instance()) {
        if (mTeraWorkHeap)
            return;

        mTeraWorkHeap = sead::ExpHeap::tryCreate(0, "TeraWork", mFixedHeap, sizeof(void*),
                                                 sead::Heap::cHeapDirection_Forward, false);
        if (mTeraWorkHeap) {
            tera::System::instance()->allocateApertureMapsCollectorImage(mTeraWorkHeap);
            mTeraWorkHeap->adjust();
            res::stubbedLogFunction();
        }
    } else {
        res::stubbedLogFunction();
    }
}

void OverlayArenaSystem::createPlacementTreeHeap() {
    res::stubbedLogFunction();
    if (!mPlacementTreeHeap) {
        mPlacementTreeHeap =
            sead::ExpHeap::tryCreate(0x700000, "PlacementTree", mFixedHeap, sizeof(void*),
                                     sead::Heap::cHeapDirection_Forward, false);
    }
    res::stubbedLogFunction();
}

void OverlayArenaSystem::createStubbed() {}

void OverlayArenaSystem::createMovieHeap() {
    res::stubbedLogFunction();
    mMovieHeap = sead::ExpHeap::tryCreate(
        0x8c00000, "MovieHeap", res::ResourceMgrTask::instance()->getTexHandleMgrArena()->mHeap,
        sizeof(void*), sead::Heap::cHeapDirection_Forward, false);
    res::stubbedLogFunction();
}

}  // namespace ksys
