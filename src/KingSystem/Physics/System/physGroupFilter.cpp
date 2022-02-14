#include "KingSystem/Physics/System/physGroupFilter.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

GroupFilter::GroupFilter(ContactLayerType type, ContactLayer::ValueType layer_first,
                         ContactLayer::ValueType layer_last)
    : mLayerFirst(layer_first), mLayerLast(layer_last), mLayerType(type) {}

GroupFilter::~GroupFilter() = default;

void GroupFilter::initFilter(sead::Heap* heap) {
    for (auto& mask : m_collisionLookupTable)
        mask = 0;

    doInit_(heap);
    doInitSystemGroupHandlerLists_(heap);
    mInhibitCollisions = false;
}

void GroupFilter::destroy() {
    for (auto& list : mFreeLists) {
        while (auto* handler = list.popFront()) {
            delete handler;
        }
    }
    delete this;
}

SystemGroupHandler* GroupFilter::addSystemGroupHandler(int free_list_idx) {
    mCS.lock();

    auto* handler = mFreeLists[free_list_idx].popFront();
    if (!handler) {
        mCS.unlock();
        return nullptr;
    }

    mUsedList.pushBack(handler);
    mCS.unlock();
    return handler;
}

void GroupFilter::removeSystemGroupHandler(SystemGroupHandler* handler) {
    auto lock = sead::makeScopedLock(mCS);

    const int free_list_idx = getFreeListIndex(handler);
    mFreeLists[free_list_idx].pushBack(handler);
    mUsedList.erase(handler);
}

u32 SystemGroupHandler::makeRagdollCollisionFilterInfo(GroundHit ground_hit) {
    return 0;
}

void SystemGroupHandler::removeThis() {
    System::instance()->removeSystemGroupHandler(this);
}

}  // namespace ksys::phys
