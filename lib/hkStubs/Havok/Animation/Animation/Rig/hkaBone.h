#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkaBone {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaBone)
    HK_DECLARE_REFLECTION()

    hkaBone() : m_lockTranslation(false) {}
    explicit hkaBone(hkFinishLoadedObjectFlag f) : m_name(f) {}

    hkStringPtr m_name;
    hkBool m_lockTranslation;
};
