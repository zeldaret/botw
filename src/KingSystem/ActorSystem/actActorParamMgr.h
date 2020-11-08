#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/System/DebugMessage.h"
#include "KingSystem/System/KingEditor.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {

namespace res {
class GParamList;
}  // namespace res

namespace act {

class ActorParam;

// FIXME: incomplete
class ActorParamMgr final : public sead::hostio::Node, public KingEditorComponent {
    SEAD_SINGLETON_DISPOSER(ActorParamMgr)
    ActorParamMgr();
    ~ActorParamMgr();

public:
    const char* getName() const override { return "AglXml"; }
    void syncData(const char* data) override;

    void init(sead::Heap* heap, sead::Heap* debug_heap);

    res::GParamList* getDummyGParamList() const;

    DebugMessage& getDebugMessage() { return mDebugMessage; }
    sead::Heap* getDebugHeap() const { return mDebugHeap; }
    sead::Heap* getTmpActorParamMgrHeap() const { return mTmpActorParamMgrHeap; }

private:
    u8 mFlags{};
    ActorParam* mParams = nullptr;
    DebugMessage mDebugMessage{"アクタパラメータ"};
    void* _e0 = nullptr;
    void* _e8 = nullptr;
    sead::Heap* mDebugHeap = nullptr;
    sead::Heap* mTmpActorParamMgrHeap = nullptr;
    sead::SafeArray<res::Handle, 28> mResHandles;
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(ActorParamMgr, 0xa00);

}  // namespace act

}  // namespace ksys
