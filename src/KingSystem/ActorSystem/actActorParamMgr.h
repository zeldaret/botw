#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
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

    DebugMessage& getDebugMessage() { return mDebugMessage; }
    sead::Heap* getDebugHeap() const { return mDebugHeap; }
    sead::Heap* getTmpActorParamMgrHeap() const { return mTmpActorParamMgrHeap; }

    void init(sead::Heap* heap, sead::Heap* debug_heap);

    ActorParam* getParam(const char* actor_name, ActorParam** out_free_param) const;
    ActorParam* loadParam(const char* actor_name, res::Handle* handle, void* x, u32 load_req_c);

    res::GParamList* getDummyGParamList() const;

private:
    enum class Flag : u8 {
        _1 = 1,
        _2 = 2,
        _4 = 4,
        _5 = _1 | _4,
    };

    void loadFiles(ActorParam* param, sead::Heap* heap, res::Handle* handle, void* x,
                   u32 load_req_c);
    bool loadActorPack(res::Handle* handle, const sead::SafeString& actor_name, u32 load_req_c);

    static constexpr s32 NumParams = 0x400;

    sead::TypedBitFlag<Flag> mFlags{};
    ActorParam* mParams = nullptr;
    DebugMessage mDebugMessage{"アクタパラメータ"};
    void* _e0 = nullptr;
    void* _e8 = nullptr;
    sead::Heap* mDebugHeap = nullptr;
    sead::Heap* mTmpActorParamMgrHeap = nullptr;
    sead::SafeArray<res::Handle, 28> mResHandles;
    mutable sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(ActorParamMgr, 0xa00);

}  // namespace act

}  // namespace ksys
