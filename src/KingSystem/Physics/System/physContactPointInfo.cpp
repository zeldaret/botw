#include "KingSystem/Physics/System/physContactPointInfo.h"
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

}  // namespace ksys::phys
