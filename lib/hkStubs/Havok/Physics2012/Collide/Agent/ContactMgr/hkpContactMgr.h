#pragma once

#include <Havok/Common/Base/hkBase.h>
#include "Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h"

class hkCollisionConstraintOwner;

class hkpCdBody;
class hkpCollidable;
class hkpContactPointProperties;
class hkpGskCache;
struct hkpProcessCollisionData;
struct hkpProcessCollisionInput;
struct hkpProcessCollisionOutput;

class hkpContactMgr : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpContactMgr)

    enum Type {
        TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR,
        TYPE_REPORT_CONTACT_MGR,
        TYPE_CONVEX_LIST_CONTACT_MGR,
        TYPE_NULL_CONTACT_MGR,
        TYPE_USER_CONTACT_MGR,
        TYPE_MAX
    };

    enum ToiAccept { TOI_ACCEPT = 0, TOI_REJECT = 1 };

    explicit hkpContactMgr(Type type) : m_type(type) {}

    HK_FORCE_INLINE hkContactPointId addContactPoint(const hkpCdBody& a, const hkpCdBody& b,
                                                     const hkpProcessCollisionInput& input,
                                                     hkpProcessCollisionOutput& output,
                                                     const hkpGskCache* contactCache,
                                                     hkContactPoint& cp);

    HK_FORCE_INLINE hkResult reserveContactPoints(int numPoints);

    HK_FORCE_INLINE void removeContactPoint(hkContactPointId cpId,
                                            hkCollisionConstraintOwner& constraintOwner);

    HK_FORCE_INLINE void processContact(const hkpCollidable& a, const hkpCollidable& b,
                                        const hkpProcessCollisionInput& input,
                                        hkpProcessCollisionData& collisionData);

    HK_FORCE_INLINE ToiAccept addToi(const hkpCdBody& a, const hkpCdBody& b,
                                     const hkpProcessCollisionInput& input,
                                     hkpProcessCollisionOutput& output, hkTime toi,
                                     hkContactPoint& cp, const hkpGskCache* gskCache,
                                     hkReal& projectedVelocity,
                                     hkpContactPointProperties& propertiesOut);

    HK_FORCE_INLINE void removeToi(class hkCollisionConstraintOwner& constraintOwner,
                                   hkpContactPointProperties& properties);

protected:
    virtual hkContactPointId addContactPointImpl(const hkpCdBody& a, const hkpCdBody& b,
                                                 const hkpProcessCollisionInput& input,
                                                 hkpProcessCollisionOutput& output,
                                                 const hkpGskCache* contactCache,
                                                 hkContactPoint& cp) = 0;
    virtual hkResult reserveContactPointsImpl(int numPoints) = 0;
    virtual void removeContactPointImpl(hkContactPointId cpId,
                                        hkCollisionConstraintOwner& constraintOwner) = 0;
    virtual void processContactImpl(const hkpCollidable& a, const hkpCollidable& b,
                                    const hkpProcessCollisionInput& input,
                                    hkpProcessCollisionData& collisionData) = 0;
    virtual ToiAccept addToiImpl(const hkpCdBody& a, const hkpCdBody& b,
                                 const hkpProcessCollisionInput& input,
                                 hkpProcessCollisionOutput& output, hkTime toi, hkContactPoint& cp,
                                 const hkpGskCache* gskCache, hkReal& projectedVelocity,
                                 hkpContactPointProperties& propertiesOut) = 0;
    virtual void removeToiImpl(class hkCollisionConstraintOwner& constraintOwner,
                               hkpContactPointProperties& properties) = 0;
    virtual void cleanup() {}

public:
    Type m_type;
};

inline hkContactPointId hkpContactMgr::addContactPoint(const hkpCdBody& a, const hkpCdBody& b,
                                                       const hkpProcessCollisionInput& input,
                                                       hkpProcessCollisionOutput& output,
                                                       const hkpGskCache* contactCache,
                                                       hkContactPoint& cp) {
    return addContactPointImpl(a, b, input, output, contactCache, cp);
}

inline hkResult hkpContactMgr::reserveContactPoints(int numPoints) {
    return reserveContactPointsImpl(numPoints);
}

inline void hkpContactMgr::removeContactPoint(hkContactPointId cpId,
                                              hkCollisionConstraintOwner& constraintOwner) {
    removeContactPointImpl(cpId, constraintOwner);
}

inline void hkpContactMgr::processContact(const hkpCollidable& a, const hkpCollidable& b,
                                          const hkpProcessCollisionInput& input,
                                          hkpProcessCollisionData& collisionData) {
    processContactImpl(a, b, input, collisionData);
}

inline hkpContactMgr::ToiAccept
hkpContactMgr::addToi(const hkpCdBody& a, const hkpCdBody& b, const hkpProcessCollisionInput& input,
                      hkpProcessCollisionOutput& output, hkTime toi, hkContactPoint& cp,
                      const hkpGskCache* gskCache, hkReal& projectedVelocity,
                      hkpContactPointProperties& propertiesOut) {
    return addToiImpl(a, b, input, output, toi, cp, gskCache, projectedVelocity, propertiesOut);
}

inline void hkpContactMgr::removeToi(hkCollisionConstraintOwner& constraintOwner,
                                     hkpContactPointProperties& properties) {
    removeToiImpl(constraintOwner, properties);
}
