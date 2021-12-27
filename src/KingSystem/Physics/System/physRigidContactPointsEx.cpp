#include "KingSystem/Physics/System/physRigidContactPointsEx.h"
#include "KingSystem/Physics/System/physMemSystem.h"

namespace ksys::phys {

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
    [&] { MemSystem::instance()->registerContactPointLayerPair(this, layer1, layer2, enabled); }();
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

}  // namespace ksys::phys
