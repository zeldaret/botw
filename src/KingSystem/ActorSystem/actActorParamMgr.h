#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/System/DebugMessage.h"
#include "KingSystem/System/KingEditor.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {

namespace res {
class Archive;
class GParamList;
class LoadRequest;
}  // namespace res

namespace act {

// FIXME: incomplete
class ActorParamMgr final : public sead::hostio::Node, public KingEditorComponent {
    SEAD_SINGLETON_DISPOSER(ActorParamMgr)
    ActorParamMgr();
    ~ActorParamMgr();

public:
    const char* getName() const override { return "AglXml"; }
    void syncData(char* data) override;

    DebugMessage& getDebugMessage() { return mDebugMessage; }
    sead::Heap* getDebugHeap() const { return mDebugHeap; }
    sead::Heap* getTmpActorParamMgrHeap() const { return mTempHeap; }

    bool checkPath(const sead::SafeString& path) const;

    void init(sead::Heap* heap, sead::Heap* debug_heap);

    ActorParam* allocParam(const char* actor_name, bool* allocated_new);
    ActorParam* getParam(const char* actor_name, ActorParam** out_free_param) const;
    ActorParam* loadParam(const char* actor_name, res::Handle* pack_handle, void* x,
                          u32 load_req_c);
    void unloadParam(ActorParam* param);

    bool requestLoadActorPack(res::Handle* handle, const sead::SafeString& actor_name,
                              u32 load_req_c);

    ActorParam* loadParamAsync(const char* actor_name, res::Handle* pack_handle,
                               bool* allocated_new, void* x, u32 load_req_c);
    bool finishLoadingActorLink(ActorParam* param, void* x);
    void loadParamAsyncStep2(ActorParam* param, res::Handle* pack_handle, void* x, u32 load_req_c);
    bool finishLoadingStep2(ActorParam* param, void* x);
    void loadExtraResAsync(ActorParam* param, res::Handle* pack_handle, void* x, u32 load_req_c);
    bool finishLoadingExtraRes(ActorParam* param, void* x);
    res::GParamList* getDummyGParamList() const;

private:
    enum class Flag : u8 {
        _1 = 1,
        _2 = 2,
        _4 = 4,
        _5 = _1 | _4,
    };

    void loadFiles(ActorParam* param, sead::Heap* heap, res::Handle* pack_handle, void* x,
                   u32 load_req_c);
    bool prepareLoadFromActorPack(sead::BufferedSafeString* path, res::LoadRequest* req, void* x,
                                  const sead::SafeString& dir_name,
                                  const sead::SafeString& extension,
                                  const sead::SafeString& file_name, res::Handle* pack_handle,
                                  u32 load_req_c, const sead::SafeString& requester);
    res::Archive* loadActorPack(res::Handle* handle, const sead::SafeString& actor_name,
                                u32 load_req_c);

    template <typename T>
    T* loadFile(ActorParam* param, ActorParam::ResourceType type, const char* dir_name_c,
                const char* extension_c, const char* name_c, res::Handle* pack_handle, void* x,
                u32 load_req_c);

    template <typename T>
    bool loadFileAsync(ActorParam* param, ActorParam::ResourceType type,
                       const sead::SafeString& dir_name, const sead::SafeString& extension,
                       const sead::SafeString& name, res::Handle* pack_handle, void* x,
                       u32 load_req_c);

    template <typename T>
    T* handleAsyncFileLoad(ActorParam* param, s32* idx, ActorParam::ResourceType type, void* x);

    void loadFilesStep2(ActorParam* param, sead::Heap* heap, res::Handle* pack_handle, void* x,
                        u32 load_req_c);

    void allocExtraResHandles(ActorParam* param, sead::Heap* heap) const;

    res::Handle& getDummyResHandle(ActorParam::ResourceType type) {
        return mDummyResources[int(type)];
    }

    static constexpr s32 NumParams = 0x400;

    sead::TypedBitFlag<Flag> mFlags{};
    ActorParam* mParams = nullptr;
    DebugMessage mDebugMessage{"アクタパラメータ"};
    void* _e0 = nullptr;
    void* _e8 = nullptr;
    sead::Heap* mDebugHeap = nullptr;
    sead::Heap* mTempHeap = nullptr;
    sead::SafeArray<res::Handle, ActorParam::NumResourceTypes> mDummyResources;
    mutable sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(ActorParamMgr, 0xa00);

}  // namespace act

}  // namespace ksys
