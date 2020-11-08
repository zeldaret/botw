#include "KingSystem/ActorSystem/actActorParam.h"
#include <prim/seadScopedLock.h>

namespace ksys::act {

ActorParam::Resources ActorParam::sDummyResources;

void ActorParam::resetDummyResources() {
    sDummyResources = {};
}

ActorParam::ActorParam() {
    mRes = {};
    mNumHandles1 = mNumHandles2 = 0;
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

    for (s32 i = 0; i < mNumHandles1; ++i)
        mHandles1[i].requestUnload();
    mNumHandles1 = 0;

    for (s32 i = 0; i < mNumHandles2; ++i)
        mHandles2[i].requestUnload();
    mNumHandles2 = 0;

    deleteResHandles();

    mActorName = "";
    _168 = 0;
    _a = 0;
    mRes = {};
    mEvent.resetSignal();
}

void ActorParam::deleteResHandles() {
    mHandles1.freeBuffer();
    mHandles2.freeBuffer();
}

bool ActorParam::isDummyParam(res::ActorLink::Users::User user) const {
    return mRes.mActorLink->getUsers().getUserName(user) == "Dummy";
}

}  // namespace ksys::act
