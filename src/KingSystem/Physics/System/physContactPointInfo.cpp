#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

ContactPointInfo* ContactPointInfo::make(sead::Heap* heap, int num, const sead::SafeString& name,
                                         int a, int b, int c) {
    return System::instance()->allocContactPointInfo(heap, num, name, a, b, c);
}

void ContactPointInfo::free(ContactPointInfo* instance) {
    System::instance()->freeContactPointInfo(instance);
}

ContactPointInfo::ContactPointInfo(const sead::SafeString& name, int a, int b, int c)
    : ContactPointInfoBase(name, a, b, c) {}

ContactPointInfo::~ContactPointInfo() = default;

void ContactPointInfo::allocPoints(sead::Heap* heap, int num) {
    mPoints.allocBufferAssert(num, heap);
}

void ContactPointInfo::freePoints() {
    mPoints.freeBuffer();
}

ContactPointInfo::Iterator::Iterator(const Points& points, int count)
    : mPoints(points.getBufferPtr()), mPointsNum(count), mPointsStart(points.getBufferPtr()) {
    for (int i = 0; i != count; ++i) {
        if (!mPoints[i]->flags.isOn(ContactPoint::Flag::Invalid))
            break;
        ++mIdx;
    }
}

ContactPointInfo::Iterator::Iterator(const Points& points, int count, IsEnd is_end)
    : mIdx(count), mPoints(points.getBufferPtr()), mPointsNum(count),
      mPointsStart(points.getBufferPtr()) {}

void ContactPointInfo::Iterator::getPointPosition(sead::Vector3f* out, Point point) const {
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

sead::Vector3f ContactPointInfo::Iterator::getPointPosition(Point point) const {
    sead::Vector3f out;
    getPointPosition(&out, point);
    return out;
}

}  // namespace ksys::phys
