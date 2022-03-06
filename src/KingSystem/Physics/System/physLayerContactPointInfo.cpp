#include "KingSystem/Physics/System/physLayerContactPointInfo.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

LayerContactPointInfo* LayerContactPointInfo::make(sead::Heap* heap, int num, int num2,
                                                   const sead::SafeString& name, int a, int b,
                                                   int c) {
    return System::instance()->allocLayerContactPointInfo(heap, num, num2, name, a, b, c);
}

void LayerContactPointInfo::free(LayerContactPointInfo* instance) {
    System::instance()->freeLayerContactPointInfo(instance);
}

bool LayerContactPointInfo::registerLayerPair(ContactLayer layer1, ContactLayer layer2,
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

bool LayerContactPointInfo::isPairUnknown(ContactLayer layer1, ContactLayer layer2) const {
    for (int i = 0; i < mLayerEntries.size(); ++i) {
        const auto* entry = mLayerEntries[i];
        if (int(layer1) == entry->layer1 && int(layer2) == entry->layer2)
            return false;
        if (int(layer1) == entry->layer2 && int(layer2) == entry->layer1)
            return false;
    }
    return true;
}

LayerContactPointInfo::LayerContactPointInfo(const sead::SafeString& name, int a, int b, int c)
    : ContactPointInfoBase(name, a, b, c) {}

LayerContactPointInfo::~LayerContactPointInfo() = default;

void LayerContactPointInfo::allocPoints(sead::Heap* heap, int num, int num2) {
    mPoints.allocBufferAssert(num, heap);
    mLayerEntries.allocBuffer(num2, heap);
}

void LayerContactPointInfo::freePoints() {
    mPoints.freeBuffer();
    mLayerEntries.freeBuffer();
}

void LayerContactPointInfo::Iterator::getPointPosition(sead::Vector3f* out, Point point) const {
    const float separating_distance = getPoint()->separating_distance;
    out->e = getPoint()->position.e;

    switch (point) {
    case Point::BodyA: {
        if (getPoint()->flags.isOn(ContactPoint::Flag::Penetrating))
            return;
        *out += getPoint()->separating_normal * -separating_distance;
        break;
    }

    case Point::BodyB: {
        if (!getPoint()->flags.isOn(ContactPoint::Flag::Penetrating))
            return;
        *out += getPoint()->separating_normal * separating_distance;
        break;
    }

    case Point::Midpoint:
    default: {
        *out += getPoint()->separating_normal * separating_distance * 0.5f;
        break;
    }
    }
}

sead::Vector3f LayerContactPointInfo::Iterator::getPointPosition(Point point) const {
    sead::Vector3f out;
    getPointPosition(&out, point);
    return out;
}

LayerContactPointInfo::Iterator::Iterator(const LayerContactPointInfo::Points& points, int count)
    : mPoints(points.getBufferPtr()), mPointsNum(count), mPointsStart(points.getBufferPtr()) {
    for (int i = 0; i != count; ++i) {
        if (!mPoints[i]->flags.isOn(ContactPoint::Flag::Invalid))
            break;
        ++mIdx;
    }
}

LayerContactPointInfo::Iterator::Iterator(const LayerContactPointInfo::Points& points, int count,
                                          IsEnd is_end)
    : mIdx(count), mPoints(points.getBufferPtr()), mPointsNum(count),
      mPointsStart(points.getBufferPtr()) {}

}  // namespace ksys::phys
