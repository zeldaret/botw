#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

ContactLayerType getContactLayerType(ContactLayer layer) {
    if (layer > ContactLayer::EntityEnd)
        return ContactLayerType::Sensor;
    return ContactLayerType::Entity;
}

u32 makeContactLayerMask(ContactLayer layer) {
    if (layer < FirstSensor)
        return 1 << layer;
    return 1 << (layer - FirstSensor);
}

u32 getContactLayerBase(ContactLayerType type) {
    if (type == ContactLayerType::Entity)
        return FirstEntity;
    return FirstSensor;
}

int getContactLayerBaseRelativeValue(ContactLayer layer) {
    return layer - (layer < FirstSensor ? FirstEntity : FirstSensor);
}

const char* contactLayerToText(ContactLayer layer) {
    return layer.text();
}

ContactLayer contactLayerFromText(const sead::SafeString& text) {
    for (auto layer : ContactLayer()) {
        if (text == layer.text())
            return layer;
    }
    return 0;
}

const char* materialToText(Material material) {
    return material.text();
}

Material materialFromText(const sead::SafeString& text) {
    for (auto material : Material()) {
        if (text == material.text())
            return material;
    }
    return 0;
}

const char* groundHitToText(GroundHit hit) {
    return hit.text();
}

GroundHit groundHitFromText(const sead::SafeString& text) {
    for (auto hit : GroundHit()) {
        if (text == hit.text())
            return hit;
    }
    return GroundHit::HitAll;
}

const char* floorCodeToText(FloorCode code) {
    return code.text();
}

FloorCode floorCodeFromText(const sead::SafeString& text) {
    for (auto code : FloorCode()) {
        if (text == code.text())
            return code;
    }
    return 0;
}

const char* wallCodeToText(WallCode code) {
    return code.text();
}

WallCode wallCodeFromText(const sead::SafeString& text) {
    for (auto code : WallCode()) {
        if (text == code.text())
            return code;
    }
    return 0;
}

MotionType motionTypeFromText(const sead::SafeString& text) {
    static constexpr const char* texts[] = {
        "Dynamic",
        "Fixed",
        "Keyframed",
    };
    static_assert(int(MotionType::Dynamic) == 0);
    static_assert(int(MotionType::Fixed) == 1);
    static_assert(int(MotionType::Keyframed) == 2);

    int type = 0;
    for (const char* type_text : texts) {
        if (text == type_text)
            return static_cast<MotionType>(type);
        ++type;
    }
    return MotionType::Unknown;
}

}  // namespace ksys::phys
