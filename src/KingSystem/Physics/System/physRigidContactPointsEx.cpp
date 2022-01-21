#include "KingSystem/Physics/System/physRigidContactPointsEx.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

RigidContactPointsEx* RigidContactPointsEx::make(sead::Heap* heap, int num, int num2,
                                                 const sead::SafeString& name, int a, int b,
                                                 int c) {
    return System::instance()->allocContactPointsEx(heap, num, num2, name, a, b, c);
}

void RigidContactPointsEx::free(RigidContactPointsEx* instance) {
    System::instance()->freeContactPointsEx(instance);
}

bool RigidContactPointsEx::registerLayerPair(ContactLayer layer1, ContactLayer layer2,
                                             bool enabled) {
    if (mLayerType == ContactLayerType::Invalid)
        mLayerType = getContactLayerType(layer1);

    if (!isPairUnknown(layer1, layer2))
        return false;

    // Add a new one.
    auto* entry = mLayerEntries.emplaceBack();
    if (entry == nullptr)
        return false;

    entry->layer1 = layer1;
    entry->layer2 = layer2;
    entry->enabled = enabled;
    [&] { System::instance()->registerContactPointLayerPair(this, layer1, layer2, enabled); }();
    return true;
}

bool RigidContactPointsEx::isPairUnknown(ContactLayer layer1, ContactLayer layer2) const {
    for (int i = 0; i < mLayerEntries.size(); ++i) {
        const auto* entry = mLayerEntries[i];
        if (int(layer1) == entry->layer1 && int(layer2) == entry->layer2)
            return false;
        if (int(layer1) == entry->layer2 && int(layer2) == entry->layer1)
            return false;
    }
    return true;
}

RigidContactPointsEx::RigidContactPointsEx(const sead::SafeString& name, int a, int b, int c)
    : IRigidContactPoints(name, a, b, c) {}

RigidContactPointsEx::~RigidContactPointsEx() = default;

void RigidContactPointsEx::allocPoints(sead::Heap* heap, int num, int num2) {
    mPoints.allocBufferAssert(num, heap);
    mLayerEntries.allocBuffer(num2, heap);
}

void RigidContactPointsEx::freePoints() {
    mPoints.freeBuffer();
    mLayerEntries.freeBuffer();
}

void RigidContactPointsEx::Iterator::getData(sead::Vector3f* out,
                                             RigidContactPointsEx::Iterator::Mode mode) const {
    const float scale = getPoint()->scale;
    out->e = getPoint()->_10.e;

    switch (mode) {
    case Mode::_0: {
        if (getPoint()->flags.isOn(ContactPoint::Flag::_2))
            return;
        *out += getPoint()->_1c * -scale;
        break;
    }

    case Mode::_1: {
        if (!getPoint()->flags.isOn(ContactPoint::Flag::_2))
            return;
        *out += getPoint()->_1c * scale;
        break;
    }

    case Mode::_2:
    default: {
        *out += getPoint()->_1c * scale * 0.5f;
        break;
    }
    }
}

sead::Vector3f
RigidContactPointsEx::Iterator::getData(RigidContactPointsEx::Iterator::Mode mode) const {
    sead::Vector3f out;
    getData(&out, mode);
    return out;
}

RigidContactPointsEx::Iterator::Iterator(const RigidContactPointsEx::Points& points, int count)
    : mPoints(points.getBufferPtr()), mPointsNum(count), mPointsStart(points.getBufferPtr()) {
    for (int i = 0; i != count; ++i) {
        if (!mPoints[i]->flags.isOn(ContactPoint::Flag::_1))
            break;
        ++mIdx;
    }
}

RigidContactPointsEx::IteratorEnd::IteratorEnd(const RigidContactPointsEx::Points& points,
                                               int count)
    : mIdx(count), mPoints(points.getBufferPtr()), mPointsNum(count),
      mPointsStart(points.getBufferPtr()) {}

}  // namespace ksys::phys
