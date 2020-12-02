#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Resource/resResourceActorLink.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::act {

namespace {

ActorConstDataAccess getAccessor(BaseProcLink* link) {
    ActorConstDataAccess accessor;
    acquireActor(link, &accessor);
    return accessor;
}

const char* sArrowTypes[] = {
    "NormalArrow", "BombArrow_A", "AncientArrow", "FireArrow", "IceArrow", "ElectricArrow",
};
gdt::FlagHandle sAnimalMasterAppearanceHandle = gdt::InvalidHandle;
gdt::FlagHandle sFairyCountCheckHandle = gdt::InvalidHandle;
gdt::FlagHandle sIsGetStopTimerLv2Handle = gdt::InvalidHandle;

}  // namespace

bool hasTag(Actor* actor, const sead::SafeString& tag) {
    if (!actor)
        return false;
    return actor->getParam()->getRes().mActorLink->hasTag(tag.cstr());
}

bool hasTag(BaseProcLink* link, const sead::SafeString& tag) {
    return hasTag(getAccessor(link), tag);
}

bool hasTag(const ActorConstDataAccess& accessor, const sead::SafeString& tag) {
    return accessor.hasTag(tag.cstr());
}

bool hasTag(const sead::SafeString& actor, const sead::SafeString& tag) {
    auto* data = InfoData::instance();
    return data && data->hasTag(actor.cstr(), tag.cstr());
}

bool hasTag(Actor* actor, u32 tag) {
    return actor && actor->getParam()->getRes().mActorLink->hasTag(tag);
}

bool hasTag(BaseProcLink* link, u32 tag) {
    return hasTag(getAccessor(link), tag);
}

bool hasTag(const ActorConstDataAccess& accessor, u32 tag) {
    return accessor.hasTag(tag);
}

bool hasTag(const sead::SafeString& actor, u32 tag) {
    auto* data = InfoData::instance();
    return data && data->hasTag(actor.cstr(), tag);
}

bool hasOneTagAtLeast(Actor* actor, const sead::SafeString& tags) {
    sead::FixedSafeString<32> tag;
    for (auto it = tags.tokenBegin(","); tags.tokenEnd(",") != it; ++it) {
        it.get(&tag);
        if (hasTag(actor, tag))
            return true;
    }
    return false;
}

bool hasOneTagAtLeast(BaseProcLink* link, const sead::SafeString& tags) {
    sead::FixedSafeString<32> tag;
    for (auto it = tags.tokenBegin(","); tags.tokenEnd(",") != it; ++it) {
        it.get(&tag);
        if (hasTag(link, tag))
            return true;
    }
    return false;
}

bool hasOneTagAtLeast(const ActorConstDataAccess& accessor, const sead::SafeString& tags) {
    sead::FixedSafeString<32> tag;
    for (auto it = tags.tokenBegin(","); tags.tokenEnd(",") != it; ++it) {
        it.get(&tag);
        if (hasTag(accessor, tag))
            return true;
    }
    return false;
}

// NON_MATCHING: this version doesn't have unnecessary register moves.
bool shouldSkipSpawnWhenRaining(map::Object* obj) {
    if (obj->getFlags().isOff(map::Object::Flag::CreateNotRain))
        return false;

    if (!world::Manager::instance())
        return false;

    const auto pos = obj->getTranslate();
    return !world::Manager::instance()->isRaining(pos);
}

bool shouldSkipSpawnIfGodForestOff(map::Object* obj) {
    bool value = false;
    if (obj->getFlags().isOff(map::Object::Flag::UnderGodForestOff))
        return false;
    if (!gdt::Manager::instance()->getBool(sAnimalMasterAppearanceHandle, &value, true))
        return false;
    return value != 0;
}

bool shouldSkipSpawnGodForestActor(map::Object* obj) {
    bool value = false;
    if (obj->getFlags().isOn(map::Object::Flag::UnderGodForest) &&
        gdt::Manager::instance()->getBool(sAnimalMasterAppearanceHandle, &value, true) && !value) {
        return true;
    }
    return shouldSkipSpawnIfGodForestOff(obj);
}

static bool isFairyCountCheckEnabled() {
    bool value = false;
    return gdt::Manager::instance()->getBool(sFairyCountCheckHandle, &value, true) && value;
}

bool shouldSkipSpawnFairy(map::Object* obj) {
    const map::ActorData& actor_data = obj->getActorData();
    if (!actor_data.mFlags.isOnBit(map::ActorData::Flag::Fairy))
        return false;

    return isFairyCountCheckEnabled();
}

bool shouldSkipSpawnFairy(const sead::SafeString& actor) {
    auto* info = InfoData::instance();
    if (!info || !info->hasTag(actor.cstr(), tags::Fairy))
        return false;

    return isFairyCountCheckEnabled();
}

void initSpawnConditionGameDataFlags() {
    sFairyCountCheckHandle = gdt::Manager::instance()->getBoolHandle("FairyCountCheck");
    sAnimalMasterAppearanceHandle =
        gdt::Manager::instance()->getBoolHandle("AnimalMaster_Appearance");
    sIsGetStopTimerLv2Handle = gdt::Manager::instance()->getBoolHandle("IsGet_Obj_StopTimerLv2");
}

// TODO: remove this once IsGetStopTimerLv2 is used
// The only purpose of this function is to prevent sIsGetStopTimerLv2Handle from being optimized out
auto initSpawnConditionGameDataFlags_dummy() {
    return sIsGetStopTimerLv2Handle;
}

}  // namespace ksys::act
