#pragma once

#include <Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Havok/Common/Base/hkBase.h>

class hkpCdBody;

struct hkpCdPoint {
    HK_DECLARE_CLASS_ALLOCATOR(hkpCdPoint)

    hkpCdPoint(const hkpCdBody& a, const hkpCdBody& b) : m_cdBodyA(a), m_cdBodyB(b) {}
    hkpCdPoint(const hkpCdBody& a, const hkpCdBody& b, const hkContactPoint& cp)
        : m_contact(cp), m_cdBodyA(a), m_cdBodyB(b) {
        m_unweldedNormal = cp.getNormal();
    }

    const hkContactPoint& getContact() const { return m_contact; }

    void setContact(const hkContactPoint& cp) {
        m_contact = cp;
        m_unweldedNormal = cp.getNormal();
    }

    void setContact(hkVector4Parameter pos, hkVector4Parameter norm, hkReal d) {
        m_contact.set(pos, norm, d);
        m_unweldedNormal = norm;
    }

    void setContact(hkVector4Parameter pos, hkVector4Parameter norm,
                    hkVector4Parameter unweldedNorm, hkReal d) {
        m_contact.set(pos, norm, d);
        m_unweldedNormal = unweldedNorm;
    }

    void setContactDistance(hkReal d) { m_contact.setDistance(d); }
    void setContactNormal(hkVector4Parameter norm) { m_contact.setNormalOnly(norm); }
    void setContactDistance(hkSimdRealParameter d) { m_contact.setDistanceSimdReal(d); }
    void setUnweldedNormal(hkVector4Parameter norm) { m_unweldedNormal = norm; }
    const hkVector4& getUnweldedNormal() const { return m_unweldedNormal; }

protected:
    hkContactPoint m_contact;
    hkVector4 m_unweldedNormal;

public:
    const hkpCdBody& m_cdBodyA;
    const hkpCdBody& m_cdBodyB;
};
