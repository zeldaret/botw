#include "KingSystem/Physics/System/physContactPointInfoEx.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

ContactPointInfoEx* ContactPointInfoEx::make(sead::Heap* heap, int num, int num2,
                                             const sead::SafeString& name, int a, int b, int c) {
    return System::instance()->allocContactPointsEx(heap, num, num2, name, a, b, c);
}

void ContactPointInfoEx::free(ContactPointInfoEx* instance) {
    System::instance()->freeContactPointInfoEx(instance);
}

bool ContactPointInfoEx::registerLayerPair(ContactLayer layer1, ContactLayer layer2, bool enabled) {
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

bool ContactPointInfoEx::isPairUnknown(ContactLayer layer1, ContactLayer layer2) const {
    for (int i = 0; i < mLayerEntries.size(); ++i) {
        const auto* entry = mLayerEntries[i];
        if (int(layer1) == entry->layer1 && int(layer2) == entry->layer2)
            return false;
        if (int(layer1) == entry->layer2 && int(layer2) == entry->layer1)
            return false;
    }
    return true;
}

ContactPointInfoEx::ContactPointInfoEx(const sead::SafeString& name, int a, int b, int c)
    : ContactPointInfoBase(name, a, b, c) {}

ContactPointInfoEx::~ContactPointInfoEx() = default;

void ContactPointInfoEx::allocPoints(sead::Heap* heap, int num, int num2) {
    mPoints.allocBufferAssert(num, heap);
    mLayerEntries.allocBuffer(num2, heap);
}

void ContactPointInfoEx::freePoints() {
    mPoints.freeBuffer();
    mLayerEntries.freeBuffer();
}

void ContactPointInfoEx::Iterator::getData(sead::Vector3f* out,
                                           ContactPointInfoEx::Iterator::Mode mode) const {
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
ContactPointInfoEx::Iterator::getData(ContactPointInfoEx::Iterator::Mode mode) const {
    sead::Vector3f out;
    getData(&out, mode);
    return out;
}

ContactPointInfoEx::Iterator::Iterator(const ContactPointInfoEx::Points& points, int count)
    : mPoints(points.getBufferPtr()), mPointsNum(count), mPointsStart(points.getBufferPtr()) {
    for (int i = 0; i != count; ++i) {
        if (!mPoints[i]->flags.isOn(ContactPoint::Flag::_1))
            break;
        ++mIdx;
    }
}

ContactPointInfoEx::IteratorEnd::IteratorEnd(const ContactPointInfoEx::Points& points, int count)
    : mIdx(count), mPoints(points.getBufferPtr()), mPointsNum(count),
      mPointsStart(points.getBufferPtr()) {}

}  // namespace ksys::phys
