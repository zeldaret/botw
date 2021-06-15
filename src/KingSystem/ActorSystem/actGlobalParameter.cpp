#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/resResourceArchive.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(GlobalParameter)

bool GlobalParameter::init(sead::Heap* heap) {
    return true;
}

void GlobalParameter::finalize() {
    if (mActorParam) {
        ActorParamMgr::instance()->unloadParam(mActorParam);
        mActorParam = nullptr;
    }

    mGlobalParam = nullptr;

    if (mResHandle.getResource())
        mResHandle.requestUnload();
}

void GlobalParameter::loadActorPack(sead::Heap* heap) {
    ActorParamMgr::instance()->requestLoadActorPack(&mResHandle, "GlobalParameter", 1);
}

bool GlobalParameter::isActorPackReady() const {
    return mResHandle.checkLoadStatus() || mResHandle.isReady();
}

bool GlobalParameter::loadActorParams() {
    return loadActorParams_();
}

bool GlobalParameter::loadActorParams_() {
    const auto* res = sead::DynamicCast<res::Archive>(mResHandle.getResource());
    if (!res)
        return false;

    void* x;
    mActorParam = ActorParamMgr::instance()->loadParam("GlobalParameter", &mResHandle, &x, 1);

    if (mActorParam->getRes().mGParamList)
        mGlobalParam = mActorParam->getRes().mGParamList->getGlobal();

    return mGlobalParam != nullptr;
}

}  // namespace ksys::act
