#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkpCollisionQualityInfo {
    HK_DECLARE_CLASS_ALLOCATOR(hkpCollisionQualityInfo)

    alignas(16) hkReal m_keepContact;
    hkReal m_create4dContact;
    hkReal m_createContact;
    hkReal m_manifoldTimDistance;
    hkBool32 m_useContinuousPhysics;
    hkBool m_useSimpleToiHandling;
    hkReal m_minSeparation;
    hkReal m_minExtraSeparation;
    hkReal m_minSafeDeltaTime;
    hkReal m_minAbsoluteSafeDeltaTime;
    hkReal m_toiSeparation;
    hkReal m_toiExtraSeparation;
    hkReal m_toiAccuracy;
    hkReal m_maxContraintViolation;
    hkReal m_minToiDeltaTime;
    hkUint16 m_constraintPriority;
    hkBool m_enableToiWeldRejection;

    hkReal calcMinSeparation(hkReal currentDistance) const { return m_minSeparation; }
};
