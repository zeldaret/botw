#pragma once

#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Object/hkReferencedObject.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>
#include <Havok/Physics2012/Collide/Filter/hkpCollidableCollidableFilter.h>
#include <Havok/Physics2012/Collide/Filter/hkpRayCollidableFilter.h>
#include <Havok/Physics2012/Collide/Filter/hkpShapeCollectionFilter.h>
#include <Havok/Physics2012/Collide/Shape/Query/hkpRayShapeCollectionFilter.h>

class hkpWorld;

class hkpCollisionFilter : public hkReferencedObject,
                           public hkpCollidableCollidableFilter,
                           public hkpShapeCollectionFilter,
                           public hkpRayShapeCollectionFilter,
                           public hkpRayCollidableFilter {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCollisionFilter)

    enum hkpFilterType {
        HK_FILTER_UNKNOWN = 0,
        HK_FILTER_NULL = 1,
        HK_FILTER_GROUP = 2,
        HK_FILTER_LIST = 3,
        HK_FILTER_CUSTOM = 4,
        HK_FILTER_PAIR = 5,
        HK_FILTER_CONSTRAINT = 6,
    };

    hkpCollisionFilter();
    explicit hkpCollisionFilter(hkFinishLoadedObjectFlag flag) : hkReferencedObject(flag) {}

    virtual void init(hkpWorld* world) {}

    hkBool isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const override = 0;

    hkBool isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
                              const hkpCdBody& b, const hkpShapeContainer& bContainer,
                              hkpShapeKey bKey) const override = 0;

    hkBool isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& collectionBodyA,
                              const hkpCdBody& collectionBodyB,
                              const hkpShapeContainer& containerShapeA,
                              const hkpShapeContainer& containerShapeB, hkpShapeKey keyA,
                              hkpShapeKey keyB) const override = 0;

    int numShapeKeyHitsLimitBreached(const hkpCollisionInput& input, const hkpCdBody& bodyA,
                                     const hkpCdBody& bodyB, const hkpBvTreeShape* bvTreeShapeB,
                                     hkAabb& aabb, hkpShapeKey* shapeKeysInOut,
                                     int shapeKeysCapacity) const override;

    hkBool isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                              const hkpShapeContainer& bContainer,
                              hkpShapeKey bKey) const override = 0;

    hkBool isCollisionEnabled(const hkpWorldRayCastInput& a,
                              const hkpCollidable& collidableB) const override = 0;

public:
    hkUint32 m_prepad[2];
    hkEnum<hkpFilterType, hkUint32> m_type;
    hkUint32 m_postpad[3];
};
