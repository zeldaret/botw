#pragma once

#include <Havok/Common/Base/hkBase.h>

// FIXME: incomplete
class hkpWorldObject : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpWorldObject)

    enum BroadPhaseType {
        BROAD_PHASE_INVALID,
        /// hkpEntity
        BROAD_PHASE_ENTITY,
        /// hkpPhantom
        BROAD_PHASE_PHANTOM,
        /// hkpBroadPhaseBorder's objects (AABB phantoms)
        BROAD_PHASE_BORDER,
        BROAD_PHASE_MAX_ID
    };
};
