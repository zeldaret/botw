#pragma once

#include <Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/Atom/hkpSimpleContactConstraintAtomUtil.h>
#include <Havok/Physics2012/Dynamics/Constraint/Contact/hkpDynamicsCpidMgr.h>

class hkpConstraintInstance;
class hkpConstraintOwner;
class hkpContactPointProperties;
class hkpRigidBody;
class hkpSimpleConstraintContactMgr;
struct hkpSimpleContactConstraintAtom;

class hkpSimpleContactConstraintData : public hkpConstraintData {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpSimpleContactConstraintData)

    explicit hkpSimpleContactConstraintData(hkFinishLoadedObjectFlag f) {}
    inline ~hkpSimpleContactConstraintData();

    inline int getNumContactPoints() const;
    inline hkContactPointId getContactPointIdAt(int index) const;
    inline const hkContactPoint& getContactPoint(int id) const;
    inline hkContactPoint& getContactPoint(int id);
    inline hkpContactPointProperties* getContactPointProperties(int id);

    hkContactPointId allocateContactPoint(hkpConstraintOwner& constraintOwner,
                                          hkContactPoint** cpOut,
                                          hkpContactPointProperties** cpPropsOut);

    int freeContactPoint(hkpConstraintOwner& constraintOwner, hkContactPointId id);

    hkBool isValid() const override;
    void getConstraintInfo(hkpConstraintData::ConstraintInfo& infoOut) const override;
    void getRuntimeInfo(hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut) const override;
    hkpSolverResults* getSolverResults(hkpConstraintRuntime* runtime) const override;
    ConstraintType getType() const override;

    virtual void collisionResponseBeginCallback(const hkContactPoint& cp,
                                                struct hkpSimpleConstraintInfoInitInput& inA,
                                                struct hkpBodyVelocity& velA,
                                                hkpSimpleConstraintInfoInitInput& inB,
                                                hkpBodyVelocity& velB);

    virtual void collisionResponseEndCallback(const hkContactPoint& cp, hkReal impulseApplied,
                                              struct hkpSimpleConstraintInfoInitInput& inA,
                                              struct hkpBodyVelocity& velA,
                                              hkpSimpleConstraintInfoInitInput& inB,
                                              hkpBodyVelocity& velB);

    hkpSimpleConstraintContactMgr* getSimpleConstraintContactMgr() const;

private:
    hkpSimpleContactConstraintData(hkpConstraintInstance* constraint, hkpRigidBody* bodyA,
                                   hkpRigidBody* bodyB);

    friend class hkpSimpleConstraintContactMgr;

public:
    hkpDynamicsCpIdMgr m_idMgrA;
    void* m_clientData;
    hkpConstraintInstance* m_constraint;
    hkpSimpleContactConstraintAtom* m_atom;
    int m_atomSize;
};

hkpSimpleContactConstraintData::~hkpSimpleContactConstraintData() {
    if (m_atom) {
        hkpSimpleContactConstraintAtomUtil::deallocateAtom(m_atom);
    }
}
