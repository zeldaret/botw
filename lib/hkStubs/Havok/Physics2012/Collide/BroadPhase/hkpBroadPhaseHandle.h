#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpBroadPhaseHandle {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpBroadPhaseHandle)

    hkpBroadPhaseHandle() : m_id(0) {}
    explicit hkpBroadPhaseHandle(hkFinishLoadedObjectFlag flag) {}

    hkUint32 m_id;
};
