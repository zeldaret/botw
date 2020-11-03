#include "KingSystem/ActorSystem/actActorTemplate.h"
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorTemplate)

ActorTemplate::~ActorTemplate() {
    util::safeDelete(mIter);
}

void ActorTemplate::init(const u8* data, sead::Heap* heap) {
    mIter = new (heap) al::ByamlIter(data);
}

bool ActorTemplate::getActorClass(const char** actor_class, const char* profile) const {
    *actor_class = "Dummy";
    al::ByamlIter iter;
    if (mIter->tryGetIterByKey(&iter, profile)) {
        if (iter.tryGetStringByKey(actor_class, "class"))
            return true;

        ActorParamMgr::instance()->getDebugMessage().log("[%s] classの定義がありません", profile);
    } else {
        ActorParamMgr::instance()->getDebugMessage().log("[%s] 未定義のアクタタイプです", profile);
    }
    return false;
}

s32 ActorTemplate::getNumAttPriorityEntries(const char* profile) const {
    al::ByamlIter iter;
    if (mIter->tryGetIterByKey(&iter, profile)) {
        al::ByamlIter attpriority;
        if (iter.tryGetIterByKey(&attpriority, "attpriority"))
            return attpriority.getSize();
    } else {
        ActorParamMgr::instance()->getDebugMessage().log("[%s] 未定義のアクタタイプです", profile);
    }
    return 0;
}

bool ActorTemplate::getAttPriority(const char** priority, const char* profile, s32 idx) const {
    *priority = "Obj";
    al::ByamlIter iter;
    if (mIter->tryGetIterByKey(&iter, profile)) {
        al::ByamlIter attpriority;
        if (!iter.tryGetIterByKey(&attpriority, "attpriority"))
            return false;

        if (attpriority.tryGetStringByIndex(priority, idx))
            return true;

        ActorParamMgr::instance()->getDebugMessage().log(
            "[%s]指定できるアテンションの優先度のインデックスが範囲外です(%d)", profile, idx);
        return false;
    }

    ActorParamMgr::instance()->getDebugMessage().log("[%s] 未定義のアクタタイプです", profile);
    return false;
}

bool ActorTemplate::getAttDefPriority(const char** priority, const char* profile) const {
    al::ByamlIter iter;
    if (mIter->tryGetIterByKey(&iter, profile)) {
        if (iter.tryGetStringByKey(priority, "attdefpriority"))
            return true;

        ActorParamMgr::instance()->getDebugMessage().log(
            "[%s] ActorTemplate.xmlでAttDefaultPriorityが未定義です", profile);
        return false;
    }

    ActorParamMgr::instance()->getDebugMessage().log("[%s] 未定義のアクタタイプです", profile);
    return false;
}

s32 ActorTemplate::getNumProfiles() const {
    return mIter->getSize();
}

const char* ActorTemplate::getProfileName(s32 idx) const {
    const char* name = nullptr;
    al::ByamlIter iter;
    mIter->tryGetIterAndKeyNameByIndex(&iter, &name, idx);
    return name;
}

}  // namespace ksys::act
