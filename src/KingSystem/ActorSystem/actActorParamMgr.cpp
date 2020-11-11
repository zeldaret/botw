#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actASSetting.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceGParamList.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorParamMgr)

ActorParamMgr::ActorParamMgr() = default;

ActorParamMgr::~ActorParamMgr() {
    ASSetting::deleteInstance();
}

// NON_MATCHING: addressing mode
ActorParam* ActorParamMgr::getParam(const char* actor_name, ActorParam** out_free_param) const {
    auto lock = sead::makeScopedLock(mCS);
    for (s32 i = 0; i < NumParams; ++i) {
        auto* param = &mParams[i];
        if (param->getActorName().isEmpty()) {
            if (out_free_param && !*out_free_param)
                *out_free_param = param;
        } else if (param->getActorName() == actor_name) {
            return param;
        }
    }
    return nullptr;
}

ActorParam* ActorParamMgr::loadParam(const char* actor_name, res::Handle* handle, void* x,
                                     u32 load_req_c) {
    ActorParam* param;
    bool existing = false;

    {
        auto lock = sead::makeScopedLock(mCS);

        ActorParam* free_param = nullptr;
        param = getParam(actor_name, &free_param);

        if (param) {
            existing = true;
        } else {
            param = free_param;
            if (free_param)
                free_param->mRes = {};
            else
                param = &mParams[NumParams - 1];

            param->mActorName = actor_name;
        }
        param->incrementRef();
    }

    if (!existing) {
        loadFiles(param, mTmpActorParamMgrHeap, handle, x, load_req_c);
        param->setEventSignal();
    } else {
        param->waitForEvent();
    }

    return param;
}

bool ActorParamMgr::loadActorPack(res::Handle* handle, const sead::SafeString& actor_name,
                                  u32 load_req_c) {
    sead::FixedSafeString<128> path;
    res::LoadRequest req;

    if (mFlags.isOn(Flag::_5))
        return false;

    path.format("Actor/Pack/%s.bactorpack", actor_name.cstr());
    req.mRequester = actor_name;
    req._c = load_req_c;
    req._8 = true;
    req._28 = false;
    return handle->requestLoad(path, &req);
}

res::GParamList* ActorParamMgr::getDummyGParamList() const {
    return static_cast<res::GParamList*>(
        mResHandles[u32(ActorParam::ResourceType::GParamList)].getResourceUnchecked());
}

}  // namespace ksys::act
