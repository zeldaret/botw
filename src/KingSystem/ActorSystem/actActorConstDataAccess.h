#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {
class Object;
class ObjectLinkData;
}  // namespace ksys::map

namespace ksys::res {
class GParamList;
class Shop;
}  // namespace ksys::res

namespace ksys::act {

class Actor;

class ActorConstDataAccess : public ActorLinkConstDataAccess {
public:
    ActorConstDataAccess() = default;
    explicit ActorConstDataAccess(BaseProc* proc) : ActorLinkConstDataAccess(proc) {}

    bool acquireActor(const ActorLinkConstDataAccess& other);

    bool hasProc() const { return ActorLinkConstDataAccess::hasProc(); }

    /// Checks whether the acquired BaseProc is `proc`.
    bool hasProc(BaseProc* proc) const;

    /// Checks whether the acquired BaseProc and the BaseProcLink's actor are the same
    /// by comparing the IDs.
    bool hasProc(const BaseProcLink& link) const;

    template <typename T>
    bool isDerivedFrom() const {
        return sead::IsDerivedFrom<T>(mProc);
    }

    bool linkAcquire(BaseProcLink* link) const;
    bool linkAcquireImmediately(BaseProcLink* link) const;

    void debugLog(s32, const sead::SafeString& method_name) const;

    bool isPlayerProfile() const;
    bool isWeaponProfile() const;
    bool isNPCProfile() const;
    bool isEnemyProfile() const;

    const sead::SafeString& getProfile() const;
    const sead::SafeString& getName() const;

    const sead::SafeString& getLiftType() const;
    bool isDisableFreezeLift() const;
    bool isDisableBurnLift() const;

    bool hasTag(const char* tag) const;
    bool hasTag(u32 tag) const;
    const char* getUniqueName() const;
    u32 getId() const;
    bool acquireConnectedCalcParent(ActorLinkConstDataAccess* accessor) const;
    bool acquireConnectedCalcChild(ActorLinkConstDataAccess* accessor) const;
    bool hasConnectedCalcParent() const;
    bool checkFlag2B() const;

    bool deleteLater(BaseProc::DeleteReason reason) const;
    bool deleteEx(BaseProc::DeleteReason reason) const;
    bool sleep(BaseProc::SleepWakeReason reason) const;
    bool wakeUp(BaseProc::SleepWakeReason reason) const;
    bool setProperties(int x, const sead::Matrix34f& mtx, const sead::Vector3f& vel,
                       const sead::Vector3f& ang_vel, const sead::Vector3f& scale,
                       bool is_life_infinite, int i, int life) const;
    bool setProperties(const sead::Matrix34f& mtx, const sead::Vector3f& vel,
                       const sead::Vector3f& ang_vel, const sead::Vector3f& scale,
                       bool is_life_infinite, int i, int life) const;
    bool isStateSleep() const;
    bool isStateCalc() const;
    bool isDeletedOrDeleting() const;

    res::GParamList* getGParamList() const;
    res::Shop* getShopData() const;

    const sead::SafeString& getAttackSpHitActor() const;
    const sead::SafeString& getAttackSpHitTag() const;
    const sead::SafeString& getAttackWeakHitTag() const;
    f32 getAttackSpHitRatio() const;
    s32 getAttackPower() const;

    map::ObjectLinkData* getMapObjectLinkData() const;
    map::Object* getMapObject() const;

    s32 getEnemyRank() const;

    bool getSameGroupActorName(sead::SafeString* name) const;

    bool checkFlag18() const;
    bool isPlayerTheConnectedParent() const;

    const sead::Vector3f& getPreviousPos() const;

    void setThisActorAsParent(BaseProc* child, bool delete_parent_on_delete);
    void setThisActorAsChild(BaseProc* parent, bool delete_child_on_delete);

    bool isAttClientEnabled(const sead::SafeString& client) const;

    bool isFlyingBalloon() const;
    u32 getBalloonHungActorBaseProcID() const;

    bool checkFlag25() const;

    f32 getHorseMoveRadius() const;
    f32 getHorseAvoidOffset() const;
    bool horseTargetedIsCircularMoveAlways() const;

private:
    Actor* getActor() const;

    u8 _10 = 0;
};
KSYS_CHECK_SIZE_NX150(ActorConstDataAccess, 0x18);

bool acquireActor(BaseProcLink* link, ActorConstDataAccess* accessor);

}  // namespace ksys::act
