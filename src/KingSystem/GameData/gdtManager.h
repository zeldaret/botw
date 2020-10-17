#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::gdt {

class IManager {
public:
    virtual ~IManager() = 0;
};

inline IManager::~IManager() = default;

/// GameDataMgr communication.
class ManagerCom {
public:
    virtual const char* getName() const { return "GameData"; }
    virtual void syncData();

    void* _8 = nullptr;
    void* _10 = nullptr;
};
KSYS_CHECK_SIZE_NX150(ManagerCom, 0x18);

// FIXME: very incomplete. This is only here because res::GameData needs to use the Manager's heaps
class Manager : public IManager, public ManagerCom {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    virtual ~Manager();

public:
    sead::Heap* getGameDataHeap() const { return mGameDataHeap; }
    sead::Heap* getSaveAreaHeap() const { return mSaveAreaHeap; }
    sead::Heap* getGameDataComHeap() const { return mGameDataComHeap; }

private:
    sead::Heap* mGameDataHeap = nullptr;
    sead::Heap* mSaveAreaHeap = nullptr;
    sead::Heap* mGameDataComHeap = nullptr;
    res::Handle mGameDataArcHandle;
    sead::SafeArray<res::Handle, 31> mBgdataHandles;
};
// FIXME: the size should be 0xDC8
KSYS_CHECK_SIZE_NX150(Manager, 0xa58);

}  // namespace ksys::gdt
