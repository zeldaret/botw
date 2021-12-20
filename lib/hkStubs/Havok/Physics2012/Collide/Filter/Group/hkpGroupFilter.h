#pragma once

#include <Havok/Physics2012/Collide/Filter/hkpCollisionFilter.h>
#include "Havok/Common/Base/Math/Vector/hkVector4.h"

class hkpGroupFilter : public hkpCollisionFilter {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpGroupFilter)

    enum {
        USE_COLLIDABLE_FILTER_INFO = 0xffffffff,
    };

    hkpGroupFilter();
    ~hkpGroupFilter() override;

    explicit hkpGroupFilter(hkFinishLoadedObjectFlag flag) : hkpCollisionFilter(flag) {
        if (flag.m_finishing) {
            m_type = HK_FILTER_GROUP;
        }
    }

    void enableCollisionsBetween(int layerA, int layerB);
    void disableCollisionsBetween(int layerA, int layerB);

    void enableCollisionsUsingBitfield(hkUint32 layerBitsA, hkUint32 layerBitsB);
    void disableCollisionsUsingBitfield(hkUint32 layerBitsA, hkUint32 layerBitsB);

    static inline hkUint32 calcFilterInfo(int layer, int systemGroup = 0, int subSystemId = 0,
                                          int subSystemDontCollideWith = 0);

    static inline int getLayerFromFilterInfo(hkUint32 filterInfo);
    static inline int setLayer(hkUint32 filterInfo, int newLayer);
    static inline int getSystemGroupFromFilterInfo(hkUint32 filterInfo);
    static inline int getSubSystemIdFromFilterInfo(hkUint32 filterInfo);
    static inline int getSubSystemDontCollideWithFromFilterInfo(hkUint32 filterInfo);

    /// Creates a new unique identifier for system groups (maximum 65k).
    inline int getNewSystemGroup();

    hkBool isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const override;

    hkBool isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
                              const hkpCdBody& b, const hkpShapeContainer& bContainer,
                              hkpShapeKey bKey) const override;

    hkBool isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& collectionBodyA,
                              const hkpCdBody& collectionBodyB,
                              const hkpShapeContainer& containerShapeA,
                              const hkpShapeContainer& containerShapeB, hkpShapeKey keyA,
                              hkpShapeKey keyB) const override;

    hkBool isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                              const hkpShapeContainer& bContainer, hkpShapeKey bKey) const override;

    hkBool isCollisionEnabled(const hkpWorldRayCastInput& inputA,
                              const hkpCollidable& collidableB) const override;

    hkBool isCollisionEnabled(hkUint32 infoA, hkUint32 infoB) const;

    virtual int dummyUnused() { return 0; }

    int m_nextFreeSystemGroup;
    hkUint32 m_collisionLookupTable[32];
    hkVector4 m_pad256[4];
};

inline hkUint32 hkpGroupFilter::calcFilterInfo(int layer, int systemGroup, int subSystemId,
                                               int subSystemDontCollideWith) {
    return (systemGroup << 16) | (subSystemDontCollideWith << 10) | (subSystemId << 5) | layer;
}

inline int hkpGroupFilter::getLayerFromFilterInfo(hkUint32 filterInfo) {
    return int(filterInfo & 0x1f);
}

inline int hkpGroupFilter::setLayer(hkUint32 filterInfo, int newLayer) {
    hkUint32 collisionLayerMask = 0xffffffff - 0x1f;
    return int(newLayer + (collisionLayerMask & filterInfo));
}

inline int hkpGroupFilter::getSystemGroupFromFilterInfo(hkUint32 filterInfo) {
    return int(filterInfo >> 16);
}

inline int hkpGroupFilter::getSubSystemIdFromFilterInfo(hkUint32 filterInfo) {
    return int((filterInfo >> 5) & 0x1f);
}

inline int hkpGroupFilter::getSubSystemDontCollideWithFromFilterInfo(hkUint32 filterInfo) {
    return int((filterInfo >> 10) & 0x1f);
}

inline int hkpGroupFilter::getNewSystemGroup() {
    return ++m_nextFreeSystemGroup;
}
