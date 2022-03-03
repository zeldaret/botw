#pragma once

#include <Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Havok/Common/Base/hkBase.h>

class hkpDynamicsCpIdMgr {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpDynamicsCpIdMgr)

    using hkpValueType = hkUchar;
    static constexpr int HK_MAX_IDS_PER_OBJECT = 8;
    static constexpr hkpValueType FREE_VALUE = 0xff;

    inline hkpDynamicsCpIdMgr();
    inline ~hkpDynamicsCpIdMgr();

    inline int newId(int value);
    inline int indexOf(int value) const;
    inline void freeId(int id);
    inline void decrementValuesGreater(int relIndex);
    inline void getAllUsedIds(hkArray<hkContactPointId>& ids) const;
    inline hkpValueType getValueAt(int id) const;

    hkInplaceArray<hkpValueType, HK_MAX_IDS_PER_OBJECT> m_values;
};

inline hkpDynamicsCpIdMgr::hkpDynamicsCpIdMgr() = default;

inline hkpDynamicsCpIdMgr::~hkpDynamicsCpIdMgr() = default;
