#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics/Constraint/Atom/hkpConstraintAtom.h>
#include <Havok/Physics/Constraint/Data/hkpConstraintInfo.h>

class hkpConstraintQueryIn;
class hkpConstraintQueryOut;
struct hkpConstraintRuntime;
class hkpSolverResults;

class hkpConstraintData : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpConstraintData)
    HK_DECLARE_REFLECTION()

    enum ConstraintType : int {
        CONSTRAINT_TYPE_BALLANDSOCKET = 0,
        CONSTRAINT_TYPE_HINGE = 1,
        CONSTRAINT_TYPE_LIMITEDHINGE = 2,
        CONSTRAINT_TYPE_POINTTOPATH = 3,
        CONSTRAINT_TYPE_PRISMATIC = 6,
        CONSTRAINT_TYPE_RAGDOLL = 7,
        CONSTRAINT_TYPE_STIFFSPRING = 8,
        CONSTRAINT_TYPE_WHEEL = 9,
        CONSTRAINT_TYPE_GENERIC = 10,
        CONSTRAINT_TYPE_CONTACT = 11,
        CONSTRAINT_TYPE_BREAKABLE = 12,
        CONSTRAINT_TYPE_MALLEABLE = 13,
        CONSTRAINT_TYPE_POINTTOPLANE = 14,
        CONSTRAINT_TYPE_PULLEY = 15,
        CONSTRAINT_TYPE_ROTATIONAL = 16,
        CONSTRAINT_TYPE_HINGE_LIMITS = 18,
        CONSTRAINT_TYPE_RAGDOLL_LIMITS = 19,
        CONSTRAINT_TYPE_CUSTOM = 20,
        CONSTRAINT_TYPE_RACK_AND_PINION = 21,
        CONSTRAINT_TYPE_COG_WHEEL = 22,
        CONSTRAINT_TYPE_FIXED = 23,
        CONSTRAINT_TYPE_DEFORMABLE_FIXED = 24,
        CONSTRAINT_TYPE_LINEAR_SLACK = 25,

        BEGIN_CONSTRAINT_CHAIN_TYPES = 100,
        CONSTRAINT_TYPE_STIFF_SPRING_CHAIN = 100,
        CONSTRAINT_TYPE_BALL_SOCKET_CHAIN = 101,
        CONSTRAINT_TYPE_POWERED_CHAIN = 102
    };

    struct ConstraintInfo : hkpConstraintInfo {
        HK_DECLARE_CLASS_ALLOCATOR(ConstraintType)
        HK_FORCE_INLINE ConstraintInfo() { m_extraSchemaSize = 0; }

        hkpConstraintAtom* m_atoms;
        hkUint32 m_sizeOfAllAtoms;
        hkUint32 m_extraSchemaSize;
    };

    struct RuntimeInfo {
        HK_DECLARE_CLASS_ALLOCATOR(RuntimeInfo)

        int m_sizeOfExternalRuntime;
        int m_numSolverResults;
    };

    HK_FORCE_INLINE hkpConstraintData();
    explicit hkpConstraintData(hkFinishLoadedObjectFlag f);
    HK_FORCE_INLINE ~hkpConstraintData() override;

    virtual ConstraintType getType() const = 0;
    virtual void getConstraintInfo(ConstraintInfo& infoOut) const = 0;
    virtual hkBool isValid() const = 0;

    virtual void setMaximumLinearImpulse(hkReal maxLinearImpulse);
    virtual void setMaximumAngularImpulse(hkReal maxAngularImpulse);
    virtual void setBreachImpulse(hkReal breachImpulse);
    virtual hkReal getMaximumLinearImpulse() const;
    virtual hkReal getMaximumAngularImpulse() const;
    virtual hkReal getBreachImpulse() const;
    virtual void setBodyToNotify(int bodyIndex);
    virtual hkUint8 getNotifiedBodyIndex() const;

    virtual void setSolvingMethod(hkpConstraintAtom::SolvingMethod method);
    virtual hkResult setInertiaStabilizationFactor(const hkReal inertiaStabilizationFactor);
    virtual hkResult getInertiaStabilizationFactor(hkReal& inertiaStabilizationFactorOut) const;

    virtual void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const = 0;
    virtual hkpSolverResults* getSolverResults(hkpConstraintRuntime* runtime) const;
    virtual void addInstance(hkpConstraintRuntime* runtime, int sizeOfRuntime) const;

    virtual void buildJacobian(const hkpConstraintQueryIn& in, hkpConstraintQueryOut& out);
    virtual hkBool isBuildJacobianCallbackRequired() const { return false; }
    virtual void buildJacobianCallback(const hkpConstraintQueryIn& in,
                                       const hkpConstraintQueryOut& out);
    static void getConstraintInfoUtil(const hkpConstraintAtom* atoms, int sizeOfAllAtoms,
                                      ConstraintInfo& infoOut);

    hkUlong m_userData;
};

inline hkpConstraintData::hkpConstraintData() {
    m_userData = 0;
}

inline hkpConstraintData::~hkpConstraintData() = default;
