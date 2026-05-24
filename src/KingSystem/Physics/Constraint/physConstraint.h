#pragma once
#include <container/seadSafeArray.h>
#include <prim/seadEnum.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadSpinLock.h>
#include "KingSystem/Physics/System/physSystem.h"

class hkQuaternionf;
class hkpConstraintInstance;
class hkpRigidBody;

namespace ksys::phys {

class RigidBody;
class StaticCompoundRigidBodyGroup;
class ConstraintParam;
class ConstraintListener;

class Constraint {
    SEAD_RTTI_BASE(Constraint)

public:
    SEAD_ENUM(ConstrainedType,Parent,Child)

    typedef void (*ConstraintCallback)(void*, Constraint* constraint, bool a2);

    Constraint(hkpConstraintInstance* constraint, RigidBody* parent, RigidBody* child,
               hkQuaternionf* quat, void* cs_option);
    virtual ~Constraint();

    bool initParent(RigidBody* body);
    bool initChild(RigidBody* body);
    bool initBody(RigidBody* body, ConstrainedType type);
    bool initWithGroup(StaticCompoundRigidBodyGroup* grp);
    bool initBodies(RigidBody* parent, RigidBody* child);

    void allocConstraintListener(sead::Heap* heap);

    void wake();
    bool setRigidBody(RigidBody* existing_body, RigidBody* body);
    bool addToWorld(bool restore_sleeping);
    void calcMass();
    void unlinkIf2Set();
    void unlink();
    void clearRigidBody(ConstrainedType type);
    void unlinkConstrainedBodies(bool activate_entity, bool world_constraint);

    void sub_7100F69FF0();
    void sub_7100F6A074();
    void setConstraintWeights(float parent_weight, float child_weight);
    void pushToSystem();
    void pushToSystem2();
    void pushToSystem4();
    void pushToSystem8();

    RigidBody* getRigidBody(s32 idx) const;
    bool isFlag2Set() const;
    bool checkIsSleeping() const;

    /// No-op if instance is null.
    static void destroy(Constraint* instance);

    enum class Flag : u16 {
        Active = 1 << 0,
        _2 = 1 << 1,
        _4 = 1 << 2,
        PendingRemove = 1 << 3,
        TOIEnabled = 1 << 4,
        IsModifyingConstrained = 1 << 5,
    };

    enum class SysFlag : u16 {
        HasSleepingBodies = 1 << 0,
        _2 = 1 << 1,
        _4 = 1 << 2,
        _8 = 1 << 3,
    };

private:
    hkpConstraintInstance* mConstraint{};
    float mDirection{};
    void* mCsOption{};
    ConstraintParam* mConstraintParam{};
    ConstraintListener* mListener{};
    sead::SafeArray<RigidBody*, 2> mActiveBodies{};
    sead::SafeArray<RigidBody*, 2> mSleepingBodies{};
    sead::TypedBitFlag<Flag> mFlags{};
    sead::TypedBitFlag<SysFlag> mSysFlags{};
    sead::CriticalSection mCS{};
    float mWeightParent = 1.0;
    float mWeightChild = 1.0;
    ConstraintCallback** mCallback{};
    sead::SpinLock mSpinLock{};
};

}  // namespace ksys::phys
