#pragma once

#include <Havok/Common/Base/Math/Vector/hkVector4.h>
#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

class hkpCollisionDispatcher;
class hkpCollisionFilter;
class hkpConvexListFilter;

struct hkpCollisionInput {
    HK_DECLARE_CLASS_ALLOCATOR(hkpCollisionInput)

    struct Aabb32Info {
        HK_DECLARE_CLASS_ALLOCATOR(hkpCollisionInput::Aabb32Info)

        hkVector4 m_bitOffsetLow;
        hkVector4 m_bitOffsetHigh;
        hkVector4 m_bitScale;
    };

    hkpCollisionDispatcher* m_dispatcher;
    hkBool32 m_weldClosestPoints;
    hkBool32 m_forceAcceptContactPoints = false;
    hkReal m_tolerance;
    const hkpCollisionFilter* m_filter;
    const hkpConvexListFilter* m_convexListFilter;
    mutable hkBool32 m_createPredictiveAgents;
    Aabb32Info m_aabb32Info;
};
