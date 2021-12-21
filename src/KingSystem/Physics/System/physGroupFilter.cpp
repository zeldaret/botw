#include "KingSystem/Physics/System/physGroupFilter.h"

namespace ksys::phys {

GroupFilter::GroupFilter(ContactLayerType type, ContactLayer::ValueType layer_first,
                         ContactLayer::ValueType layer_last)
    : mIdxLayerFirst(layer_first), mIdxLayerLast(layer_last), mLayerType(type) {}

GroupFilter::~GroupFilter() = default;

void GroupFilter::m13() {}

}  // namespace ksys::phys
