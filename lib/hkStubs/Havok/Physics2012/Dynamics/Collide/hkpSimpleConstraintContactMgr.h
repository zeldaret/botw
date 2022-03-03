#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Dispatch/ContactMgr/hkpContactMgrFactory.h>
#include <Havok/Physics2012/Dynamics/Collide/hkpDynamicsContactMgr.h>
#include <Havok/Physics2012/Dynamics/Constraint/Atom/hkpModifierConstraintAtom.h>
#include <Havok/Physics2012/Dynamics/Constraint/Contact/hkpSimpleContactConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>

class hkpRigidBody;

extern const hkClass hkpSimpleConstraintContactMgrClass;

class hkpSimpleConstraintContactMgr : public hkpDynamicsContactMgr {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpSimpleConstraintContactMgr)

    hkpSimpleConstraintContactMgr(hkpWorld* world, hkpRigidBody* bodyA, hkpRigidBody* bodyB);
    ~hkpSimpleConstraintContactMgr() override;

    explicit hkpSimpleConstraintContactMgr(hkFinishLoadedObjectFlag f)
        : hkpDynamicsContactMgr(hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR),
          m_contactConstraintData(f), m_constraint(f) {
        m_constraint.m_uid = 0xffffffff;
    }

    hkContactPoint* getContactPoint(hkContactPointId id) override;
    hkpContactPointProperties* getContactPointProperties(hkContactPointId id) override;

    hkContactPointId addContactPointImpl(const hkpCdBody& a, const hkpCdBody& b,
                                         const hkpProcessCollisionInput& input,
                                         hkpProcessCollisionOutput& output,
                                         const hkpGskCache* contactCache,
                                         hkContactPoint& cp) override;
    hkResult reserveContactPointsImpl(int numPoints) override;
    void removeContactPointImpl(hkContactPointId cpId,
                                hkCollisionConstraintOwner& constraintOwner) override;
    void processContactImpl(const hkpCollidable& a, const hkpCollidable& b,
                            const hkpProcessCollisionInput& input,
                            hkpProcessCollisionData& collisionData) override;
    ToiAccept addToiImpl(const hkpCdBody& a, const hkpCdBody& b,
                         const hkpProcessCollisionInput& input, hkpProcessCollisionOutput& output,
                         hkTime toi, hkContactPoint& cp, const hkpGskCache* gskCache,
                         hkReal& projectedVelocity, hkpContactPointProperties& properties) override;
    void removeToiImpl(class hkCollisionConstraintOwner& constraintOwner,
                       hkpContactPointProperties& properties) override;
    hkBool fireCallbacksForEarliestToi(struct hkpToiEvent& event, hkReal& rotateNormal) override;
    void confirmToi(struct hkpToiEvent& event, hkReal rotateNormal,
                    class hkArray<class hkpEntity*>& outToBeActivated) override;
    void cleanup() override { delete this; }
    Type getType() const override { return TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR; }
    void getAllContactPointIds(hkArray<hkContactPointId>& contactPointIds) const override;

    HK_FORCE_INLINE hkpSimpleContactConstraintAtom* getAtom() {
        return m_contactConstraintData.m_atom;
    }

    HK_FORCE_INLINE const hkpSimpleContactConstraintAtom* getAtom() const {
        return m_contactConstraintData.m_atom;
    }

    hkpConstraintInstance* getConstraintInstance() override;
    virtual const hkpConstraintInstance* getConstraintInstance() const;

    void toiCollisionResponseBeginCallback(const hkContactPoint& cp,
                                           struct hkpSimpleConstraintInfoInitInput& inA,
                                           struct hkpBodyVelocity& velA,
                                           hkpSimpleConstraintInfoInitInput& inB,
                                           hkpBodyVelocity& velB) override;

    void toiCollisionResponseEndCallback(const hkContactPoint& cp, hkReal impulseApplied,
                                         struct hkpSimpleConstraintInfoInitInput& inA,
                                         struct hkpBodyVelocity& velA,
                                         hkpSimpleConstraintInfoInitInput& inB,
                                         hkpBodyVelocity& velB) override;

    inline hkBool isConstraintDisabled() const {
        return m_constraint.getConstraintModifiers() &&
               (m_constraint.getConstraintModifiers()->getType() ==
                hkpConstraintAtom::TYPE_MODIFIER_IGNORE_CONSTRAINT);
    }

protected:
    inline hkpRigidBody* setContactPointProperties(const hkpCdBody& a, const hkpCdBody& b,
                                                   int maxNumExtraDataInEvent,
                                                   hkpContactPointProperties* cpi);

    const hkClass* getClassType() const override { return &hkpSimpleConstraintContactMgrClass; }

public:
    class Factory : public hkpContactMgrFactory {
    public:
        HK_DECLARE_CLASS_ALLOCATOR(Factory)

        explicit Factory(hkpWorld* mgr);

        hkpContactMgr* createContactMgr(const hkpCollidable& a, const hkpCollidable& b,
                                        const hkpCollisionInput& input) override;

    protected:
        hkpWorld* m_world;
    };

public:
    hkUint16 m_reservedContactPoints;
    hkUint16 m_contactPointCallbackDelay;

    hkpSimpleContactConstraintData m_contactConstraintData;
    hkpConstraintInstance m_constraint;

    hkUint32 m_pad[1];
};
