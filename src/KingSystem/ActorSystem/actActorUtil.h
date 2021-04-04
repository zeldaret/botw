#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace al {
class ByamlIter;
}

namespace ksys::map {
class Object;
}

namespace ksys::act {

class Actor;
class ActorConstDataAccess;
class BaseProcLink;

enum class ArrowType {
    /// Wooden arrows.
    Normal = 0,
    /// Bomb arrows.
    Bomb = 1,
    /// Ancient arrows.
    Ancient = 2,
    /// Fire arrows.
    Fire = 3,
    /// Ice arrows.
    Ice = 4,
    /// Shock arrows.
    Electric = 5,

    Invalid = -1,
};

/// Compendium type (図鑑 type).
enum class ZukanType {
    Animal = 0,
    Enemy = 1,
    /// Materials (素材).
    Sozai = 2,
    Weapon = 3,
    Other = 4,
    Invalid = 5,
};

bool hasTag(Actor* actor, const sead::SafeString& tag);
bool hasTag(BaseProcLink* link, const sead::SafeString& tag);
bool hasTag(const ActorConstDataAccess& accessor, const sead::SafeString& tag);
bool hasTag(const sead::SafeString& actor, const sead::SafeString& tag);

bool hasTag(Actor* actor, u32 tag);
bool hasTag(BaseProcLink* link, u32 tag);
bool hasTag(const ActorConstDataAccess& accessor, u32 tag);
bool hasTag(const sead::SafeString& actor, u32 tag);

/// Checks whether the actor has at least one of the specified tags.
/// @param tags A comma separated list of tags.
bool hasOneTagAtLeast(Actor* actor, const sead::SafeString& tags);
bool hasOneTagAtLeast(BaseProcLink* link, const sead::SafeString& tags);
bool hasOneTagAtLeast(const ActorConstDataAccess& accessor, const sead::SafeString& tags);

bool shouldSkipSpawnWhenRaining(map::Object* obj);
bool shouldSkipSpawnIfGodForestOff(map::Object* obj);
bool shouldSkipSpawnGodForestActor(map::Object* obj);
bool shouldSkipSpawnFairy(map::Object* obj);
bool shouldSkipSpawnFairy(const sead::SafeString& actor);

/// Must be called before using any of the "should skip" functions above.
void initSpawnConditionGameDataFlags();

bool hasAnyRevivalTag(const sead::SafeString& actor);

bool hasStopTimerMiddleTag(Actor* actor);
bool hasStopTimerShortTag(Actor* actor);
bool canBeStasised(Actor* actor, bool force);

void highlightStasisableActors(bool on);

const char* arrowTypeToString(ArrowType idx);
ArrowType arrowTypeFromString(const sead::SafeString& name);

ZukanType getZukanType(al::ByamlIter* iter);
ZukanType getZukanType(Actor* actor);

bool isPlayerProfile(const ActorConstDataAccess& accessor);
bool isPlayerProfile(Actor* actor);
bool isPlayerProfile(BaseProcLink* link);

bool isCameraProfile(Actor* actor);

bool isNPCProfile(const ActorConstDataAccess& accessor);
bool isNPCProfile(Actor* actor);
bool isNPCProfile(BaseProcLink* link);
bool isNPCOffPodFromWeapon(Actor* actor);

bool isDemoNPCProfile(Actor* actor);

bool isEnemyProfile(const ActorConstDataAccess& accessor);
bool isEnemyProfile(Actor* actor);
bool isEnemyProfile(BaseProcLink* link);

bool isGuardianProfile(BaseProcLink* link);

bool isLargeEnemy(const ActorConstDataAccess& accessor);
bool isLargeEnemy(Actor* actor);

bool isGanonBeast(const ActorConstDataAccess& accessor);
bool isGanonBeast(BaseProcLink* link);

bool isNotLivingCreature(Actor* actor);
bool isNotLivingCreature(const ActorConstDataAccess& accessor);
bool isNotLivingCreature(BaseProcLink* link);

bool isWeaponProfile(const ActorConstDataAccess& accessor);
bool isWeaponProfile(const sead::SafeString& actor);
bool isWeaponProfile(Actor* actor);
bool isWeaponProfile(BaseProcLink* link);

bool isWeaponOrArmor(const ActorConstDataAccess& accessor);
bool isWeaponOrArmor(Actor* actor);

bool isBulletProfile(const ActorConstDataAccess& accessor);
bool isBulletProfile(Actor* actor);
bool isBulletProfile(BaseProcLink* link);

bool isHorseProfile(const ActorConstDataAccess& accessor);
bool isHorseProfile(Actor* actor);
bool isHorseProfile(BaseProcLink* link);

bool isAttClientEnabled(Actor* actor, const sead::SafeString& client);
bool isGrabAttClientEnabled(void* x, BaseProcLink* link);

bool isStalfosParts(BaseProcLink* link);

bool isDoor(const ActorConstDataAccess& accessor);
bool isDoor(BaseProcLink* link);

bool isPreyOrSwarm(const ActorConstDataAccess& accessor);
bool isPreyOrSwarm(Actor* actor);
bool isPreyOrSwarm(BaseProcLink* link);

bool isWolfOrBear(const ActorConstDataAccess& accessor);
bool isWolfOrBear(Actor* actor);
bool isWolfOrBear(BaseProcLink* link);

bool isRope(Actor* actor);
bool isRope(BaseProcLink* link);

bool isTreeOrScaffoldOrSignboard(Actor* actor);

bool isAlive(BaseProcLink* link);

bool isAirOctaPlatform(const sead::SafeString& name);
bool isAirOctaWoodPlatformDlc(const sead::SafeString& name);

const sead::SafeString& getDefaultDropActor();

void getRevivalGridPosition(const sead::Vector3f& pos, int* col1, int* row1, int* col2, int* row2);

bool getSameGroupActorName(sead::SafeString* name, BaseProcLink* link);
bool getSameGroupActorName(sead::SafeString* name, Actor* actor);
bool getSameGroupActorName(sead::SafeString* name, const sead::SafeString& default_value,
                           al::ByamlIter* actor_info);
bool getSameGroupActorName(sead::SafeString* name, const sead::SafeString& actor_name);

}  // namespace ksys::act
