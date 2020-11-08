#include "KingSystem/ActorSystem/actActorParam.h"
#include <prim/seadScopedLock.h>

namespace ksys::act {

ActorParam::Resources ActorParam::sDummyResources;

void ActorParam::resetDummyResources() {
    sDummyResources = {};
}

ActorParam::ActorParam() {
    mRes = {};
    mNumHandles = {};
    mEvent.resetSignal();
}

ActorParam::~ActorParam() {
    deleteData();
}

// NON_MATCHING: b.le -> b.lt
void ActorParam::deleteData() {
    auto lock = sead::makeScopedLock(mCS);

    if (mActorName.isEmpty())
        return;

    for (size_t i = 0; i < mNumHandles.size(); ++i) {
        for (s32 handle_idx = 0; handle_idx < mNumHandles[i]; ++handle_idx)
            mHandles[i][handle_idx].requestUnload();
        mNumHandles[i] = 0;
    }

    deleteResHandles();

    mActorName = "";
    _168 = 0;
    _a = 0;
    mRes = {};
    mEvent.resetSignal();
}

void ActorParam::deleteResHandles() {
    for (auto& handles : mHandles)
        handles.freeBuffer();
}

bool ActorParam::isDummyParam(res::ActorLink::Users::User user) const {
    return mRes.mActorLink->getUsers().getUserName(user) == "Dummy";
}

}  // namespace ksys::act
