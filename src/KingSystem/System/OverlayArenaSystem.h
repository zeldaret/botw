#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadDelegate.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/System/OverlayArenaSystemS1.h"
#include "KingSystem/System/OverlayArenaSystemS2.h"
#include "KingSystem/Utils/Thread/Event.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
class SZSDecompressor;
}  // namespace sead

namespace ksys {

namespace util {
class Task;
class TaskThread;
}  // namespace util

class OverlayArena;
class SystemPauseMgr;

// FIXME: incomplete
class OverlayArenaSystem {
    SEAD_SINGLETON_DISPOSER(OverlayArenaSystem)

    OverlayArenaSystem();
    virtual ~OverlayArenaSystem();

public:
    struct InitArg {
        SystemPauseMgr* system_pause_mgr;
    };

    bool init(const InitArg& arg, sead::Heap* heap);

    void getSzsDecompressor(sead::SZSDecompressor** decompressor) const;
    OverlayArena* getArena() const;
    OverlayArena* getTeraSzsWorkArena() const;
    OverlayArena* getAudioArena() const;
    OverlayArena* getUnknownArena() const;

    sead::Heap* getFixedHeap() const { return mFixedHeap; }
    sead::Heap* getMovableMemoryHeap() const { return mMovableMemoryHeap; }
    sead::Heap* getGameDataWorkHeap() const { return mGameDataWorkHeap; }
    sead::Heap* getMovieHeap() const { return mMovieHeap; }
    sead::Heap* getPlacementTreeHeap() const { return mPlacementTreeHeap; }
    sead::Heap* getTeraWorkHeap() const { return mTeraWorkHeap; }
    sead::Heap* getSzsDecompressorInstHeap() const { return mSzsDecompressorInstHeap; }
    sead::Heap* getSzsHeap() const { return mSzsHeap; }
    sead::Heap* getTexArcWorkHeap() const { return mTexArcWorkHeap; }

    void createTeraWorkHeap();
    void createStubbed();
    void createMovieHeap();

private:
    enum class Flag {
        _1 = 0x1,
        _2 = 0x2,
    };

    void createHeaps();
    void destroyHeaps();

    void createSzsDecompressor();
    void createTexArcWorkHeap();
    void createArena();
    void createTeraSzsWorkArena();
    void createAudioArena();
    void createJpegHeap();
    void createPlacementTreeHeap();

    bool delegatedFunction();

    sead::TypedBitFlag<Flag, u8> mFlags;
    u32 _2c = 0;
    sead::Heap* mFixedHeap = nullptr;
    sead::Heap* mMovableMemoryHeap = nullptr;
    sead::Heap* mGameDataWorkHeap = nullptr;
    sead::Heap* mMovieHeap = nullptr;
    sead::Heap* mPlacementTreeHeap = nullptr;
    sead::Heap* mTeraWorkHeap = nullptr;
    sead::Heap* mSzsDecompressorInstHeap = nullptr;
    sead::Heap* mSzsHeap = nullptr;
    sead::SZSDecompressor* mSzsDecompressor = nullptr;
    sead::Heap* mTexArcWorkHeap = nullptr;
    OverlayArena* mArena = nullptr;
    OverlayArena* mTeraSzsWorkArena = nullptr;
    OverlayArena* mAudioArena = nullptr;
    OverlayArena* mUnknownArena = nullptr;
    sead::Heap* mJpegHeap = nullptr;
    SystemPauseMgr* mSystemPauseMgr = nullptr;
    OverlayArenaSystemS1 mS1;
    u32 _b8 = 0;
    util::TaskThread* mPrepareThread = nullptr;
    util::Task* mTask = nullptr;
    sead::DelegateR<OverlayArenaSystem, bool> mDelegate;
    OverlayArenaSystemS2 mS2;
    sead::Atomic<u32> _130 = 0;
    sead::Atomic<u32> _134 = 0;
    res::Handle mResHandle;
    util::Event mEvent;
};
KSYS_CHECK_SIZE_NX150(OverlayArenaSystem, 0x1c8);

}  // namespace ksys
