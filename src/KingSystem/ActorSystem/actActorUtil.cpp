#include "KingSystem/ActorSystem/actActorUtil.h"
#include <container/seadSafeArray.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Resource/Actor/resResourceActorLink.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::act {

namespace {

ActorConstDataAccess getAccessor(BaseProcLink* link) {
    ActorConstDataAccess accessor;
    acquireActor(link, &accessor);
    return accessor;
}

ActorConstDataAccess getAccessor(Actor* actor) {
    ActorConstDataAccess accessor{actor};
    return accessor;
}

sead::SafeString sDefaultDropActor = "Item_Fruit_A";
sead::SafeArray<const char*, 6> sArrowTypes{{
    "NormalArrow",
    "BombArrow_A",
    "AncientArrow",
    "FireArrow",
    "IceArrow",
    "ElectricArrow",
}};
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

// NON_MATCHING: redundant branches in the original code.
bool hasAnyRevivalTag(const sead::SafeString& actor) {
    auto* info = InfoData::instance();
    al::ByamlIter iter;
    if (!info || !info->getActorIter(&iter, actor.cstr()))
        return false;

    for (auto tag : {
             tags::RevivalBloodyMoon,
             tags::RevivalRandom,
             tags::RevivalNone,
             tags::RevivalNoneForUsed,
             tags::RevivalRandomForDrop,
             tags::RevivalNoneForDrop,
             tags::RevivalUnderGodTime,
         }) {
        if (info->hasTag(iter, tag))
            return true;
    }
    return false;
}

bool hasStopTimerMiddleTag(Actor* actor) {
    return hasTag(actor, tags::StopTimerMiddle);
}

bool hasStopTimerShortTag(Actor* actor) {
    return hasTag(actor, tags::StopTimerShort);
}

// NON_MATCHING: ???
const char* arrowTypeToString(ArrowType idx) {
    return sArrowTypes[u32(idx)];
}

ArrowType arrowTypeFromString(const sead::SafeString& name) {
    for (s32 i = 0; i < sArrowTypes.size(); ++i) {
        if (name == sArrowTypes[i])
            return ArrowType(i);
    }
    return ArrowType::Invalid;
}

ZukanType getZukanType(al::ByamlIter* iter) {
    if (!iter)
        return ZukanType::Invalid;

    auto* info = InfoData::instance();

    if (info->hasTag(*iter, tags::ZukanAnimal))
        return ZukanType::Animal;

    if (info->hasTag(*iter, tags::ZukanEnemy))
        return ZukanType::Enemy;

    if (info->hasTag(*iter, tags::ZukanSozai))
        return ZukanType::Sozai;

    if (info->hasTag(*iter, tags::ZukanWeapon))
        return ZukanType::Weapon;

    if (info->hasTag(*iter, tags::ZukanOther))
        return ZukanType::Other;

    return ZukanType::Invalid;
}

ZukanType getZukanType(Actor* actor) {
    if (!actor)
        return ZukanType::Invalid;

    if (hasTag(actor, tags::ZukanAnimal))
        return ZukanType::Animal;

    if (hasTag(actor, tags::ZukanEnemy))
        return ZukanType::Enemy;

    if (hasTag(actor, tags::ZukanSozai))
        return ZukanType::Sozai;

    if (hasTag(actor, tags::ZukanWeapon))
        return ZukanType::Weapon;

    if (hasTag(actor, tags::ZukanOther))
        return ZukanType::Other;

    return ZukanType::Invalid;
}

static bool isProfile(const ActorConstDataAccess& accessor, const sead::SafeString& profile) {
    return accessor.hasProc() && accessor.getProfile() == profile;
}

bool isPlayerProfile(const ActorConstDataAccess& accessor) {
    return isProfile(accessor, "Player");
}

bool isPlayerProfile(Actor* actor) {
    return isPlayerProfile(getAccessor(actor));
}

bool isPlayerProfile(BaseProcLink* link) {
    return isPlayerProfile(getAccessor(link));
}

const sead::SafeString& getDefaultDropActor() {
    return sDefaultDropActor;
}

bool isCameraProfile(Actor* actor) {
    return isProfile(getAccessor(actor), "Camera");
}

bool isNPCProfile(const ActorConstDataAccess& accessor) {
    return isProfile(accessor, "NPC");
}

bool isNPCProfile(Actor* actor) {
    return isNPCProfile(getAccessor(actor));
}

bool isNPCProfile(BaseProcLink* link) {
    return isNPCProfile(getAccessor(link));
}

bool isNPCOffPodFromWeapon(Actor* actor) {
    if (!actor)
        return false;

    auto* gparam = actor->getParam()->getRes().mGParamList;
    if (!gparam)
        return false;

    const auto* npc_param = gparam->getNpc();
    return npc_param && npc_param->mIsOffPodFromWeapon.ref();
}

bool isDemoNPCProfile(Actor* actor) {
    return isProfile(getAccessor(actor), "DemoNPC");
}

bool isEnemyProfile(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    const auto& profile = accessor.getProfile();

    return profile == "Enemy" || profile == "GiantEnemy" || profile == "Guardian" ||
           profile == "GuardianComponent" || profile == "LastBoss" || profile == "GelEnemy" ||
           profile == "EnemySwarm" || profile == "SiteBoss" || profile == "Sandworm" ||
           profile == "Dragon";
}

bool isEnemyProfile(Actor* actor) {
    return isEnemyProfile(getAccessor(actor));
}

bool isEnemyProfile(BaseProcLink* link) {
    return isEnemyProfile(getAccessor(link));
}

bool isGuardianProfile(BaseProcLink* link) {
    const auto accessor = getAccessor(link);
    if (!accessor.hasProc())
        return false;

    const auto& profile = accessor.getProfile();
    return profile == "Guardian" || profile == "GuardianComponent";
}

bool isLargeEnemy(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    const auto& profile = accessor.getProfile();
    return profile == "GiantEnemy" || profile == "LastBoss" || profile == "SiteBoss" ||
           profile == "Sandworm" || profile == "Dragon";
}

bool isLargeEnemy(Actor* actor) {
    return isLargeEnemy(getAccessor(actor));
}

bool isGanonBeast(const ActorConstDataAccess& accessor) {
    return accessor.hasProc() && accessor.getName() == "Enemy_GanonBeast";
}

bool isGanonBeast(BaseProcLink* link) {
    return isGanonBeast(getAccessor(link));
}

bool isNotLivingCreature(Actor* actor) {
    return isNotLivingCreature(getAccessor(actor));
}

bool isNotLivingCreature(const ActorConstDataAccess& accessor) {
    if (isPlayerProfile(accessor))
        return false;
    if (isNPCProfile(accessor))
        return false;
    if (isEnemyProfile(accessor))
        return false;
    if (isHorseProfile(accessor))
        return false;
    if (isPreyOrSwarm(accessor))
        return false;
    return true;
}

bool isNotLivingCreature(BaseProcLink* link) {
    return isNotLivingCreature(getAccessor(link));
}

bool isWeaponProfile(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;
    return isWeaponProfile(accessor.getName());
}

bool isWeaponProfile(const sead::SafeString& actor) {
    const char* profile = nullptr;
    InfoData::instance()->getActorProfile(&profile, actor.cstr());
    return sead::SafeString(profile).startsWith("Weapon");
}

bool isWeaponProfile(Actor* actor) {
    return isWeaponProfile(getAccessor(actor));
}

bool isWeaponProfile(BaseProcLink* link) {
    return isWeaponProfile(getAccessor(link));
}

bool isWeaponOrArmor(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    const auto& name = accessor.getName();
    const char* profile_cstr = nullptr;
    InfoData::instance()->getActorProfile(&profile_cstr, name.cstr());

    const sead::SafeString profile = profile_cstr;
    return profile.startsWith("Weapon") || profile.startsWith("OptionalWeapon") ||
           profile.startsWith("Armor");
}

bool isWeaponOrArmor(Actor* actor) {
    return isWeaponOrArmor(getAccessor(actor));
}

bool isBulletProfile(const ActorConstDataAccess& accessor) {
    return isProfile(accessor, "Bullet");
}

bool isBulletProfile(Actor* actor) {
    return isBulletProfile(getAccessor(actor));
}

bool isBulletProfile(BaseProcLink* link) {
    return isBulletProfile(getAccessor(link));
}

bool isHorseProfile(const ActorConstDataAccess& accessor) {
    return isProfile(accessor, "Horse");
}

bool isHorseProfile(Actor* actor) {
    return isHorseProfile(getAccessor(actor));
}

bool isHorseProfile(BaseProcLink* link) {
    return isHorseProfile(getAccessor(link));
}

bool isGrabAttClientEnabled(void*, BaseProcLink* link) {
    return getAccessor(link).isAttClientEnabled("Grab");
}

bool isStalfosParts(BaseProcLink* link) {
    const auto accessor = getAccessor(link);
    return accessor.hasProc() && accessor.hasTag(tags::StalfosParts);
}

bool isDoor(const ActorConstDataAccess& accessor) {
    return accessor.hasProc() && accessor.hasTag(tags::Door);
}

bool isDoor(BaseProcLink* link) {
    return isDoor(getAccessor(link));
}

bool isPreyOrSwarm(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;
    const auto& profile = accessor.getProfile();
    return profile == "Prey" || profile == "Swarm";
}

bool isPreyOrSwarm(Actor* actor) {
    return isPreyOrSwarm(getAccessor(actor));
}

bool isPreyOrSwarm(BaseProcLink* link) {
    return isPreyOrSwarm(getAccessor(link));
}

bool isWolfOrBear(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;
    return accessor.hasTag(tags::AnimalTypeWolf) || accessor.hasTag(tags::AnimalTypeBear);
}

bool isWolfOrBear(Actor* actor) {
    return isWolfOrBear(getAccessor(actor));
}

bool isWolfOrBear(BaseProcLink* link) {
    return isWolfOrBear(getAccessor(link));
}

bool isRope(Actor* actor) {
    const auto accessor = getAccessor(actor);
    return accessor.hasProc() && accessor.isDerivedFrom<RopeBase>();
}

bool isRope(BaseProcLink* link) {
    const auto accessor = getAccessor(link);
    return accessor.hasProc() && accessor.isDerivedFrom<RopeBase>();
}

bool isTreeOrScaffoldOrSignboard(Actor* actor) {
    const auto accessor = getAccessor(actor);
    if (!accessor.hasProc())
        return false;

    return accessor.hasTag(tags::Tree) || accessor.hasTag(tags::Scaffold) ||
           accessor.hasTag(tags::Signboard);
}

bool isAirOctaPlatform(const sead::SafeString& name) {
    return name == "Obj_BoardWood_Square_01" || name == "Obj_BoardWood_Triangle_01" ||
           name == "FldObj_DLC_FlyShield_A_Snow_01" || name == "FldObj_DLC_FlyShield_A_Snow_02";
}

bool isAirOctaWoodPlatformDlc(const sead::SafeString& name) {
    return name == "FldObj_DLC_FlyShield_Wood_A_02" ||
           name == "FldObj_DLC_FlyShield_Wood_A_Snow_02";
}

void getRevivalGridPosition(const sead::Vector3f& pos, int* col1, int* row1, int* col2, int* row2) {
    const int col = sead::clamp((int(pos.x) + 5000) / 1000, 0, 9);
    const int row = sead::clamp((int(pos.z) + 4000) / 1000, 0, 7);

    const auto x = (float(col) + 0.5f) * 1000.0f - 5000.0f;
    const auto z = (float(row) + 0.5f) * 1000.0f - 4000.0f;

    if (x < pos.x) {
        *col1 = col;
        *col2 = col + 1;
    } else {
        *col1 = col - 1;
        *col2 = col;
    }

    if (z < pos.z) {
        *row1 = row;
        *row2 = row + 1;
    } else {
        *row1 = row - 1;
        *row2 = row;
    }
}

bool getSameGroupActorName(sead::SafeString* name, BaseProcLink* link) {
    return getAccessor(link).getSameGroupActorName(name);
}

bool getSameGroupActorName(sead::SafeString* name, Actor* actor) {
    return getAccessor(actor).getSameGroupActorName(name);
}

bool getSameGroupActorName(sead::SafeString* name, const sead::SafeString& default_value,
                           al::ByamlIter* actor_info) {
    const sead::SafeString value = InfoData::instance()->getSameGroupActorName(*actor_info);
    if (value.isEmpty()) {
        *name = default_value;
        return false;
    }
    *name = value;
    return true;
}

bool getSameGroupActorName(sead::SafeString* name, const sead::SafeString& actor_name) {
    const sead::SafeString value = InfoData::instance()->getSameGroupActorName(actor_name.cstr());
    if (value.isEmpty()) {
        *name = actor_name;
        return false;
    }
    *name = value;
    return true;
}

}  // namespace ksys::act
