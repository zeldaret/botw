#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCdBody.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>

class hkpShapeContainer;

namespace hkBvTreeAgent3 {

HK_FORCE_INLINE const hkpShapeContainer* getShapeContainerFrom(const hkpCdBody* body);

}  // namespace hkBvTreeAgent3

inline const hkpShapeContainer* hkBvTreeAgent3::getShapeContainerFrom(const hkpCdBody* body) {
    auto* shape = static_cast<const hkpBvTreeShape*>(body->getShape());
    return shape->getContainer();
}
