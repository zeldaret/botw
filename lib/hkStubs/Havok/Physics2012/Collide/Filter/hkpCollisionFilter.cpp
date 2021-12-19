#include <Havok/Physics2012/Collide/Filter/hkpCollisionFilter.h>

hkpCollisionFilter::hkpCollisionFilter() : m_type(HK_FILTER_UNKNOWN) {}

int hkpCollisionFilter::numShapeKeyHitsLimitBreached(const hkpCollisionInput& input,
                                                     const hkpCdBody& bodyA, const hkpCdBody& bodyB,
                                                     const hkpBvTreeShape* bvTreeShapeB,
                                                     hkAabb& aabb, hkpShapeKey* shapeKeysInOut,
                                                     int shapeKeysCapacity) const {
    return shapeKeysCapacity;
}
