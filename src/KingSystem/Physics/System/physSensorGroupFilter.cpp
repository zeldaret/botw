#include "KingSystem/Physics/System/physSensorGroupFilter.h"
#include <basis/seadRawPrint.h>

namespace ksys::phys {

u32 sensorReceiverMaskSetLayer(ContactLayer layer, u32 mask) {
    SEAD_ASSERT(getContactLayerType(layer) == ContactLayerType::Sensor);

    ReceiverMask info{mask};

    if (layer == ContactLayer::SensorCustomReceiver) {
        info.is_custom_receiver = true;
    } else {
        if (info.is_custom_receiver) {
            clearBitFields(&info.raw, info.is_custom_receiver, info.custom_receiver_data.layer);
        } else {
            clearBitFields(&info.raw, info.is_custom_receiver, info.data.layer,
                           info.data.has_layer2, info.data.layer2);
        }

        if (info.is_custom_receiver) {
            info.custom_receiver_data.layer.Init(layer - FirstSensor);
        } else {
            info.data.layer.Init(layer - FirstSensor);
        }
    }

    return info.raw;
}

u32 sensorReceiverMaskSetLayer2(bool set, ContactLayer layer, u32 mask) {
    SEAD_ASSERT(getContactLayerType(layer) == ContactLayerType::Sensor);

    ReceiverMask info{mask};
    if (info.is_custom_receiver)
        return info.raw;

    info.is_custom_receiver = false;
    info.data.has_layer2 = false;
    info.data.layer2 = {};

    if (set) {
        info.data.has_layer2 = true;
        info.data.layer2.SetUnsafe(layer - FirstSensor);
    }

    return info.raw;
}

}  // namespace ksys::phys
