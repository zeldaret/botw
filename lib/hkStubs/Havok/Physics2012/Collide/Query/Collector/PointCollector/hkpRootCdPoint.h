#pragma once

#include <Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeBase.h>

class hkpCollidable;

struct hkpRootCdPoint {
    HK_DECLARE_CLASS_ALLOCATOR(hkpRootCdPoint)

    hkBool32 operator<(const hkpRootCdPoint& b) const {
        return m_contact.getDistanceSimdReal().isLess(b.m_contact.getDistanceSimdReal());
    }

    const hkContactPoint& getContact() const { return m_contact; }

    void setContact(const hkContactPoint& cp) { m_contact = cp; }

    void setContact(hkVector4Parameter pos, hkVector4Parameter norm, hkReal d) {
        m_contact.set(pos, norm, d);
    }
    void setContact(hkVector4Parameter pos, hkVector4Parameter norm, hkSimdRealParameter d) {
        m_contact.setPositionNormalAndDistance(pos, norm, d);
    }

    void setContactDistance(hkReal d) { m_contact.setDistance(d); }
    void setContactDistance(hkSimdRealParameter d) { m_contact.setDistanceSimdReal(d); }

    hkContactPoint m_contact;
    const hkpCollidable* m_rootCollidableA;
    hkpShapeKey m_shapeKeyA;
    const hkpCollidable* m_rootCollidableB;
    hkpShapeKey m_shapeKeyB;
};
