#include "KingSystem/Physics/System/physRayCast.h"
#include "KingSystem/Physics/physLayerMaskBuilder.h"

namespace ksys::phys {

RayCast::RayCast(SystemGroupHandler* group_handler, GroundHit ground_hit)
    : mGroupHandler(group_handler), mGroundHit(ground_hit) {
    reset();
}

RayCast::~RayCast() = default;

// NON_MATCHING: reorderings
void RayCast::reset() {
    mTo = sead::Vector3f::zero;
    mFrom = sead::Vector3f::zero;
    mLayerMasks = {};
    mExtraGroupHandlers.clear();

    resetCastResult();
}

void RayCast::resetCastResult() {
    static_cast<void>(_98.load());

    _30 = {};
    _34 = sead::Vector3f::zero;
    mHitFraction = -1.0;
    _48 = {};
    _50 = {};
    _54 = {};
    _58 = {};
    _60 = {};
    _70 = {};
}

static bool isLayerValid(ContactLayer layer, ContactLayerType type) {
    if (type == ContactLayerType::Entity) {
        if (layer > ContactLayer::EntityHitOnlyGround)
            return false;
    } else {
        if (layer > ContactLayer::SensorNoHit)
            return false;
    }

    return true;
}

void RayCast::enableLayer(ContactLayer layer) {
    auto type = getContactLayerType(layer);
    if (!isLayerValid(layer, type))
        return;

    const auto mask = makeContactLayerMask(layer);
    getLayerMask(type).set(mask);
}

void RayCast::disableLayer(ContactLayer layer) {
    auto type = getContactLayerType(layer);
    if (!isLayerValid(layer, type))
        return;

    getLayerMask(type).resetBit(getContactLayerBaseRelativeValue(layer));
}

void RayCast::setLayers(const LayerMaskBuilder& builder) {
    for (int i = 0; i < NumContactLayerTypes; ++i)
        mLayerMasks[i] = builder.getMasks()[i].layers;
}

bool RayCast::isLayerEnabled(ContactLayer layer) const {
    auto type = getContactLayerType(layer);
    if (!isLayerValid(layer, type))
        return false;

    return getLayerMask(type).isOnBit(getContactLayerBaseRelativeValue(layer));
}

void RayCast::setGroundHit(GroundHit ground_hit) {
    mGroundHit = ground_hit;
}

GroundHit RayCast::getGroundHit() const {
    return mGroundHit;
}

void RayCast::setD8(int value) {
    _d8 = value;
}

void RayCast::set9A(bool value) {
    _9a = value;
}

void RayCast::setStart(const sead::Vector3f& start) {
    mFrom = start;
}

void RayCast::setEnd(const sead::Vector3f& end) {
    mTo = end;
}

void RayCast::setStartAndEnd(const sead::Vector3f& start, const sead::Vector3f& end) {
    setStart(start);
    setEnd(end);
}

void RayCast::setStartAndDisplacement(const sead::Vector3f& start,
                                      const sead::Vector3f& displacement) {
    setStart(start);
    setEnd(start + displacement);
}

void RayCast::setStartAndDisplacementScaled(const sead::Vector3f& start,
                                            const sead::Vector3f& displacement,
                                            float displacement_scale) {
    setStart(start);
    setEnd(start + displacement * displacement_scale);
}

bool RayCast::addGroupHandler(SystemGroupHandler* group_handler) {
    if (mExtraGroupHandlers.size() == mExtraGroupHandlers.capacity() || group_handler == nullptr)
        return false;

    mExtraGroupHandlers.pushBack(group_handler);
    return true;
}

void RayCast::setRigidBody(RigidBody* body) {
    if (_70 != 1)
        mRigidBody = body;
}

void RayCast::getHitPosition(sead::Vector3f* out) const {
    *out = ((1 - mHitFraction) * mFrom) + (mHitFraction * mTo);
}

void RayCast::get34(sead::Vector3f* out) const {
    *out = _34;
}

}  // namespace ksys::phys
