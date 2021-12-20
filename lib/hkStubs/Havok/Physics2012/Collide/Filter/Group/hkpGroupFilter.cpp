#include <Havok/Physics2012/Collide/Filter/Group/hkpGroupFilter.h>

hkpGroupFilter::hkpGroupFilter() {
    m_type = HK_FILTER_GROUP;
    for (auto& x : m_collisionLookupTable)
        x = 0xffffffff;
    m_nextFreeSystemGroup = 0;
}

hkpGroupFilter::~hkpGroupFilter() = default;
