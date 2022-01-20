#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkStepInfo {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkStepInfo)

    hkStepInfo() {}
    hkStepInfo(hkTime startTime, hkTime endTime) { set(startTime, endTime); }

    void set(hkTime startTime, hkTime endTime) {
        m_startTime = startTime;
        m_endTime = endTime;
        m_deltaTime = endTime - startTime;
        m_invDeltaTime = m_deltaTime == 0.0f ? 0.0f : 1.0f / m_deltaTime;
    }

public:
    alignas(16) hkTime m_startTime;
    hkTime m_endTime;
    hkReal m_deltaTime;
    hkReal m_invDeltaTime;
};
