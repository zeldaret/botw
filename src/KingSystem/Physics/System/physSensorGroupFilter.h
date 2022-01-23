#pragma once

#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Physics/System/physGroupFilter.h"

namespace ksys::phys {

// FIXME
class SensorGroupFilter : public GroupFilter {
    SEAD_RTTI_OVERRIDE(SensorGroupFilter, GroupFilter)
public:
    static SensorGroupFilter* make(ContactLayer::ValueType last, sead::Heap* heap);
};

/// Set the contact layer in a sensor receiver mask.
/// @param layer A sensor contact layer
/// @param mask An existing receiver mask
u32 sensorReceiverMaskSetLayer(ContactLayer layer, u32 mask);

/// Set or clear a second contact layer in a sensor receiver mask.
/// This function does nothing when using a custom receiver.
/// @param set If true, set the specified layer. Clear it otherwise
/// @param layer A sensor contact layer
/// @param mask An existing receiver mask
// TODO: rename once we figure out what this layer is used for
u32 sensorReceiverMaskSetLayer2(bool set, ContactLayer layer, u32 mask);

}  // namespace ksys::phys
