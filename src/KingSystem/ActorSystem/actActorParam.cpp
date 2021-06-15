#include "KingSystem/ActorSystem/actActorParam.h"
#include <basis/seadRawPrint.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/ActorSystem/actActorTemplate.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"
#include "KingSystem/Resource/Actor/resResourceASList.h"
#include "KingSystem/Resource/Actor/resResourceAttClient.h"
#include "KingSystem/Resource/Actor/resResourceRagdollConfig.h"
#include "KingSystem/Resource/Actor/resResourceRagdollConfigList.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/ParamIO.h"

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
    mRefCount = 0;
    _a = 0;
    mRes = {};
    mEvent.resetSignal();
}

void ActorParam::deleteResHandles() {
    for (auto& handles : mHandles)
        handles.freeBuffer();
}

bool ActorParam::isDummyParam(res::ActorLink::User user) const {
    return sead::SafeString(mRes.mActorLink->getUserName(user)) == "Dummy";
}

void ActorParam::allocResHandles(sead::Heap* heap, u32 buffer_idx, s32 count) {
    SEAD_ASSERT(buffer_idx == 0 || buffer_idx == 1);
    mHandles[buffer_idx].allocBufferAssert(count, heap);
    mNumHandles[buffer_idx] = 0;
}

s32 ActorParam::incrementRef() {
    auto lock = sead::makeScopedLock(mCS);
    return ++mRefCount;
}

s32 ActorParam::decrementRef() {
    auto lock = sead::makeScopedLock(mCS);

    if (mActorName.isEmpty())
        return 0;

    if (--mRefCount == 0)
        deleteData();

    return mRefCount;
}

void ActorParam::setEventSignal() {
    mEvent.setSignal();
}

void ActorParam::waitForEvent() {
    mEvent.wait();
}

bool ActorParam::isSignalSet() const {
    return mEvent.isSignalSet();
}

int ActorParam::updateResource(const char* data, char* data1, char* data2) {
    for (int i = 0; i < mRes.mArray.size(); ++i) {
        if (mRes.mArray[i] && mRes.mArray[i]->getPath().include(data)) {
            if (mRes.mArray[i]->ParamIO_m0(data1))
                return 1;
            if (mRes.mArray[i]->applyResourceUpdate(data1, data2))
                return 0;
        }
    }

    for (int i = 0; i < mRes.mASList->getASDefines().size(); ++i) {
        if (mRes.mASList->getASDefines()[i].as &&
            mRes.mASList->getASDefines()[i].as->getPath().include(data)) {
            if (mRes.mASList->getASDefines()[i].as->ParamIO_m0(data1))
                return 1;
            if (mRes.mASList->getASDefines()[i].as->applyResourceUpdate(data1, data2))
                return 0;
        }
    }

    auto* atcllist = mRes.mAttClientList;
    for (int i = 0; i < atcllist->getClients().size(); ++i) {
        auto* client = atcllist->getClients()[i].client;
        if (client->getPath().include(data)) {
            if (client->ParamIO_m0(data1))
                return 1;
            if (client->applyResourceUpdate(data1, data2))
                return 0;
        }
    }

    auto* rgconfiglist = mRes.mRagdollConfigList;
    for (int i = 0; i < rgconfiglist->getImpulseParams().size(); ++i) {
        auto* config = rgconfiglist->getImpulseParams()[i].config;
        if (config->getPath().include(data)) {
            if (config->ParamIO_m0(data1))
                return 1;
            if (config->applyResourceUpdate(data1, data2))
                return 0;
        }
    }

    return 2;
}

res::Handle* ActorParam::allocHandle() {
    const auto idx = mNumHandles[mActiveBufferIdx];
    ++mNumHandles[mActiveBufferIdx];
    return &mHandles[mActiveBufferIdx][idx];
}

void ActorParam::freeLastHandle() {
    --mNumHandles[mActiveBufferIdx];
}

void ActorParam::setResource(ResourceType type, ParamIO* param_io) {
    const auto idx = u32(type);
    mRes.mArray[idx] = param_io;
    param_io->setIndex(idx);
}

bool ActorParam::setPriority(const sead::SafeString& priority) {
    if (priority == "PlayerBefore") {
        mPriority = Priority::PlayerBefore;
        return true;
    }

    if (priority == "Player") {
        mPriority = Priority::Player;
        return true;
    }

    if (priority == "PlayerAfter") {
        mPriority = Priority::PlayerAfter;
        return true;
    }

    if (priority == "AllAfter") {
        mPriority = Priority::AllAfter;
        return true;
    }

    return false;
}

void ActorParam::setProfileAndPriority(const char* profile, const char* priority) {
    mProfile = profile;

    al::ByamlIter* root = ActorTemplate::instance()->getRootIter();
    al::ByamlIter iter;
    if (root->tryGetIterByKey(&iter, profile)) {
        const char* profile_priority;
        iter.tryGetStringByKey(&mClassName, "class");
        iter.tryGetStringByKey(&profile_priority, "priority");

        if (setPriority(priority))
            return;

        if (setPriority(profile_priority))
            return;

        ActorParamMgr::instance()->getDebugMessage().log(
            "[%s] アクタテンプレート %s の 処理順指定[%s:%s]は定義されていません",
            mActorName.cstr(), profile, priority, profile_priority);
    } else {
        ActorParamMgr::instance()->getDebugMessage().log(
            "[%s] アクタテンプレートに %s は定義されていません", mActorName.cstr(), profile);
        setProfileAndPriority("Dummy", priority);
    }
}

void ActorParam::onLoadFinished(ActorParamMgr*) {}

}  // namespace ksys::act
