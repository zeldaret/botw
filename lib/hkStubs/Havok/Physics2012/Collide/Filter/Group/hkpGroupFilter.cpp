#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCdBody.h>
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Havok/Physics2012/Collide/Agent/hkpCollisionInput.h>
#include <Havok/Physics2012/Collide/Filter/Group/hkpGroupFilter.h>
#include <Havok/Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeContainer.h>

hkpGroupFilter::hkpGroupFilter() {
    m_type = HK_FILTER_GROUP;
    for (auto& x : m_collisionLookupTable)
        x = 0xffffffff;
    m_nextFreeSystemGroup = 0;
}

hkpGroupFilter::~hkpGroupFilter() = default;
