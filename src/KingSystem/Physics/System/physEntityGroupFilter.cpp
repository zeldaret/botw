#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include <heap/seadHeap.h>
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

constexpr int NumEntityHandlersInList0 = 0x10;
constexpr int NumEntityHandlers = 0x400;

EntityGroupFilter* EntityGroupFilter::make(ContactLayer::ValueType first,
                                           ContactLayer::ValueType last, sead::Heap* heap) {
    auto* filter = util::alloc<EntityGroupFilter>(heap, first, last);
    filter->initFilter(heap);
    return filter;
}

EntityGroupFilter::EntityGroupFilter(ContactLayer::ValueType first, ContactLayer::ValueType last)
    : GroupFilter(ContactLayerType::Entity, first, last) {}

EntityGroupFilter::~EntityGroupFilter() = default;

void EntityGroupFilter::doInit_(sead::Heap* heap) {
    // Enable all collisions by default.
    mMasks.fill(0xffffffff);
}

void EntityGroupFilter::doInitSystemGroupHandlerLists_(sead::Heap* heap) {
    for (auto& list : mFreeLists)
        list.initOffset(SystemGroupHandler::getFreeListNodeOffset());

    mUsedList.initOffset(SystemGroupHandler::getUsedListNodeOffset());

    for (int i = 1; i < NumEntityHandlers; ++i) {
        auto& list = mFreeLists[i < NumEntityHandlersInList0];
        list.pushBack(new (heap) EntitySystemGroupHandler(i, 0));
    }
}

int EntityGroupFilter::getFreeListIndex(const SystemGroupHandler* handler) {
    return handler->getIndex() < NumEntityHandlersInList0;
}

}  // namespace ksys::phys
