#pragma once

#include "KingSystem/Physics/System/physGroupFilter.h"

namespace ksys::phys {

// FIXME
class SensorGroupFilter : public GroupFilter {
    SEAD_RTTI_OVERRIDE(SensorGroupFilter, GroupFilter)
public:
    static SensorGroupFilter* make(ContactLayer::ValueType last, sead::Heap* heap);
};

}  // namespace ksys::phys
