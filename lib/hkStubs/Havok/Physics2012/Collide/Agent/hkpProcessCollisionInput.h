#pragma once

#include <Havok/Common/Base/Types/Physics/hkStepInfo.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Agent/hkpCollisionInput.h>

struct hkpAgent1nSector;
struct hkpCollisionAgentConfig;
struct hkpCollisionQualityInfo;

struct hkpProcessCollisionInput : hkpCollisionInput {
    HK_DECLARE_CLASS_ALLOCATOR(hkpProcessCollisionInput)

    hkStepInfo m_stepInfo;
    mutable hkpCollisionQualityInfo* m_collisionQualityInfo;
    mutable hkpAgent1nSector* m_spareAgentSector;
    void* m_dynamicsInfo;
    hkBool m_enableDeprecatedWelding;
    hkBool m_allowToSkipConfirmedCallbacks;
    hkpCollisionAgentConfig* m_config;
};
