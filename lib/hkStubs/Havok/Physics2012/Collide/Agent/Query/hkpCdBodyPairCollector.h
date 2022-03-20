#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpCdBody;

class hkpCdBodyPairCollector {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCdBodyPairCollector)

    inline hkpCdBodyPairCollector();
    virtual ~hkpCdBodyPairCollector();

    virtual void addCdBodyPair(const hkpCdBody& bodyA, const hkpCdBody& bodyB) = 0;
    virtual void reset();

    inline hkBool getEarlyOut() const;

protected:
    hkBool m_earlyOut;
};

inline hkpCdBodyPairCollector::hkpCdBodyPairCollector() {
    reset();
}

inline hkpCdBodyPairCollector::~hkpCdBodyPairCollector() = default;

inline void hkpCdBodyPairCollector::reset() {
    m_earlyOut = true;
}

inline hkBool hkpCdBodyPairCollector::getEarlyOut() const {
    return m_earlyOut;
}
