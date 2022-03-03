#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpSimpleContactConstraintDataInfo {
public:
    HK_DECLARE_REFLECTION()
    HK_DECLARE_CLASS_ALLOCATOR(hkpSimpleContactConstraintDataInfo)

    enum {
        HK_FLAG_OK = 0,
        HK_FLAG_POINT_REMOVED = 1 << 0,
        HK_FLAG_AREA_CHANGED = 1 << 2,
    };

    hkpSimpleContactConstraintDataInfo() { init(); }
    explicit hkpSimpleContactConstraintDataInfo(hkFinishLoadedObjectFlag f) {}

    void init() {
        m_flags = HK_FLAG_OK;
        m_biNormalAxis = 3;
        m_contactRadius = 0.0f;
        m_internalData1.setZero();
        m_rhsRolling[0].setZero();
        m_rhsRolling[1].setZero();
        m_rollingFrictionMultiplier.setZero();
        for (int i = 0; i < 4; ++i) {
            m_data[i] = 0;
        }
    }

    alignas(16) hkUint16 m_flags;
    hkUint16 m_biNormalAxis;
    hkHalf m_rollingFrictionMultiplier;
    hkHalf m_internalData1;
    hkHalf m_rhsRolling[2];
    hkReal m_contactRadius;
    hkReal m_data[4];
};
