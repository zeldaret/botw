#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/BitField.h"

namespace ksys::phys {

enum class ContactLayerType {
    Entity,
    Sensor,
    Invalid,
};

constexpr int NumContactLayerTypes = 2;

SEAD_ENUM(ContactLayer,
EntityObject,\
EntitySmallObject,\
EntityGroundObject,\
EntityPlayer,\
EntityNPC,\
EntityRagdoll,\
EntityWater,\
EntityAirWall,\
EntityGround,\
EntityGroundSmooth,\
EntityGroundRough,\
EntityRope,\
EntityTree,\
EntityNPC_NoHitPlayer,\
EntityHitOnlyWater,\
EntityWallForClimb,\
EntityHitOnlyGround,\
EntityQueryCustomReceiver,\
EntityForbidden18,\
EntityNoHit,\
EntityMeshVisualizer,\
EntityForbidden21,\
EntityForbidden22,\
EntityForbidden23,\
EntityForbidden24,\
EntityForbidden25,\
EntityForbidden26,\
EntityForbidden27,\
EntityForbidden28,\
EntityForbidden29,\
EntityForbidden30,\
EntityEnd,\
SensorObject,\
SensorSmallObject,\
SensorPlayer,\
SensorEnemy,\
SensorNPC,\
SensorHorse,\
SensorRope,\
SensorAttackPlayer,\
SensorAttackEnemy,\
SensorChemical,\
SensorTerror,\
SensorHitOnlyInDoor,\
SensorInDoor,\
SensorReserve13,\
SensorReserve14,\
SensorChemicalElement,\
SensorAttackCommon,\
SensorQueryOnly,\
SensorTree,\
SensorCamera,\
SensorMeshVisualizer,\
SensorNoHit,\
SensorReserve20,\
SensorCustomReceiver,\
SensorEnd)

constexpr int MaxNumLayersPerType = 32;

constexpr auto FirstEntity = ContactLayer::EntityObject;
constexpr auto LastEntity = ContactLayer::EntityMeshVisualizer;

constexpr auto FirstSensor = ContactLayer::SensorObject;
constexpr auto LastSensor = ContactLayer::SensorCustomReceiver;

// If the values of the two following constants are changed, most of the BitFields defined
// in this file will need to be updated.
constexpr int NumRegularEntityLayers = ContactLayer::EntityHitOnlyGround - FirstEntity + 1;
constexpr int NumRegularSensorLayers = ContactLayer::SensorMeshVisualizer - FirstSensor + 1;
static_assert(NumRegularEntityLayers == 17);
static_assert(NumRegularSensorLayers == 21);

constexpr bool isEntityGroundLayer(ContactLayer::ValueType layer) {
    return layer == ContactLayer::EntityGround || layer == ContactLayer::EntityGroundSmooth ||
           layer == ContactLayer::EntityGroundRough;
}

SEAD_ENUM(Material,
Undefined,\
Soil,\
Stone,\
Sand,\
Metal,\
WireNet,\
Grass,\
Wood,\
Water,\
Snow,\
Ice,\
Lava,\
Bog,\
HeavySand,\
Cloth,\
Glass,\
Bone,\
Rope,\
CharControl,\
Ragdoll,\
Surfing,\
GuardianFoot,\
HeavySnow,\
Unused0,\
LaunchPad,\
Conveyer,\
Rail,\
Grudge,\
Meat,\
Vegetable,\
Bomb,\
MagicBall,\
Barrier,\
AirWall,\
Misc,\
GrudgeSlow
)

constexpr bool isInvalidMaterial(Material::ValueType mat) {
    return mat >= Material::size();
}

SEAD_ENUM(GroundHit,
Player,\
Animal,\
NPC,\
Camera,\
AttackHitPlayer,\
AttackHitEnemy,\
Arrow,\
Bomb,\
Magnet,\
CameraBody,\
IK,\
Grudge,\
MovingTrolley,\
LineOfSight,\
Giant,\
HitAll,\
Ignore
)

SEAD_ENUM(FloorCode,
None,\
Return,\
FlowStraight,\
FlowLeft,\
FlowRight,\
Slip,\
NarrowPlace,\
TopBroadleafTree,\
TopConiferousTree,\
Fall,\
Attach,\
NoImpulseUpperMove,\
NoPreventFall
)

SEAD_ENUM(WallCode,
None,\
NoClimb,\
Hang,\
LadderUp,\
Ladder,\
Slip,\
LadderSide,\
NoSlipRain,\
NoDashUpAndNoClimb,\
IceMakerBlock
)

enum class MotionType {
    Dynamic = 0,
    Fixed = 1,
    Keyframed = 2,
    Unknown = 3,
    Invalid = -1,
};

enum class GroundCollisionMode {
    /// Ground collision is not handled in any special way.
    Normal = 0,
    /// Any collision with a non-ground layer is ignored.
    IgnoreNonGround = 1,
    /// Any collision with a ground layer is ignored.
    IgnoreGround = 2,
};

enum class WaterCollisionMode {
    /// Water collision is not handled in any special way.
    Normal = 0,
    /// Any collision with a water layer is ignored.
    IgnoreWater = 1,
};

union EntityCollisionMask {
    union Data {
        ContactLayer getLayer() const { return int(layer); }
        ContactLayer getLayerSensor() const { return int(layer + FirstSensor); }
        GroundHit getGroundHit() const { return int(ground_hit); }

        u32 raw;
        util::BitField<0, 5, u32> layer;
        // TODO: figure out what this is
        util::BitField<5, 5, u32> unk5;
        util::BitField<10, 5, u32> unk10;
        /// Layers to collide with for EntityQueryCustomReceiver entities.
        util::BitField<5, NumRegularEntityLayers, u32> query_custom_receiver_layer_mask;
        util::BitField<24, 1, u32> unk24;
        util::BitField<25, 1, u32> unk25;
        util::BitField<26, 4, u32> ground_hit;
    };

    union GroundHitMask {
        ContactLayer getLayer() const { return int(layer); }

        void addGroundHit(GroundHit hit) {
            raw |= (1 << hit) << decltype(ground_hit_types)::StartBit();
        }

        u32 raw;
        util::BitField<0, 1, u32> unk;
        util::BitField<8, 16, u32> ground_hit_types;
        util::BitField<23, 1, u32> unk23;
        util::BitField<25, 5, u32> layer;
    };

    constexpr explicit EntityCollisionMask(u32 raw_ = 0) : raw(raw_) {}
    constexpr EntityCollisionMask(const EntityCollisionMask&) = default;
    constexpr EntityCollisionMask& operator=(const EntityCollisionMask& m) {
        raw = m.raw;
        return *this;
    }

    bool operator==(EntityCollisionMask rhs) const { return raw == rhs.raw; }
    bool operator!=(EntityCollisionMask rhs) const { return raw != rhs.raw; }

    static EntityCollisionMask make(ContactLayer layer, GroundHit ground_hit) {
        EntityCollisionMask mask;
        mask.data.layer.Init(layer);
        mask.data.ground_hit.Init(ground_hit);
        return mask;
    }

    ContactLayer getLayer() const {
        return is_ground_hit_mask ? ground_hit.getLayer() : data.getLayer();
    }

    ContactLayer getLayerSensor() const {
        return is_ground_hit_mask ? ContactLayer(ContactLayer::SensorCustomReceiver) :
                                    data.getLayerSensor();
    }

    GroundHit getGroundHit() const {
        return is_ground_hit_mask ? GroundHit::HitAll : data.getGroundHit();
    }

    u32 raw;
    Data data;
    GroundHitMask ground_hit;
    util::BitField<5, 2, GroundCollisionMode, u32> ground_col_mode;
    util::BitField<7, 1, WaterCollisionMode, u32> water_col_mode;
    util::BitField<16, 10, u32> group_handler_index;
    /// If this flag is set, then this entity will always collide with ground or water,
    /// regardless of the configured GroundCollisionMode or WaterCollisionMode modes.
    // TODO: is this "is_ragdoll"? See EntitySystemGroupHandler::makeCollisionFilterInfo.
    util::BitField<30, 1, bool, u32> unk30;
    util::BitField<31, 1, bool, u32> is_ground_hit_mask;
};
static_assert(sizeof(EntityCollisionMask) == sizeof(u32));

/// Collision mask that is used for raycast-based queries against entities.
union EntityQueryCollisionMask {
    constexpr explicit EntityQueryCollisionMask(u32 raw_ = 0) : raw(raw_) {}
    constexpr EntityQueryCollisionMask(const EntityQueryCollisionMask&) = default;
    constexpr EntityQueryCollisionMask& operator=(const EntityQueryCollisionMask& m) {
        raw = m.raw;
        return *this;
    }
    constexpr bool operator==(EntityQueryCollisionMask rhs) const { return raw == rhs.raw; }
    constexpr bool operator!=(EntityQueryCollisionMask rhs) const { return raw != rhs.raw; }

    util::BitField<0, NumRegularEntityLayers, u32> layer_mask;
    util::BitField<17, 1, u32> unk;
    util::BitField<18, 10, u32> group_handler_index;
    util::BitField<28, 4, GroundHit::ValueType, u32> ground_hit_type;
    u32 raw;
};

union SensorCollisionMask {
    struct CustomReceiverTag {};

    union Data {
        ContactLayer getLayer() const { return int(layer) + FirstSensor; }

        /// The sensor's contact layer.
        /// @note Add FirstSensor to get the actual ContactLayer value.
        util::BitField<0, 5, u32> layer;
        /// Whether `ignored_layer` contains a valid layer.
        util::BitField<5, 1, bool, u32> has_ignored_layer;
        /// Contact layer to ignore during collision detection. Only valid if `has_ignored_layer`.
        /// @note Add FirstSensor to get the actual ContactLayer value.
        util::BitField<6, 5, u32> ignored_layer;
    };

    union CustomReceiverData {
        util::BitField<0, NumRegularSensorLayers, u32> layer;
        util::BitField<0, NumRegularSensorLayers, u32> layer_mask;
    };

    constexpr SensorCollisionMask() : raw(0) {}
    constexpr explicit SensorCollisionMask(CustomReceiverTag) : raw(0) {
        is_custom_receiver = true;
    }
    constexpr explicit SensorCollisionMask(u32 raw_) : raw(raw_) {}
    constexpr SensorCollisionMask(const SensorCollisionMask&) = default;
    constexpr SensorCollisionMask& operator=(const SensorCollisionMask& m) {
        raw = m.raw;
        return *this;
    }

    static SensorCollisionMask make(ContactLayer layer) {
        SensorCollisionMask mask;
        if (layer == ContactLayer::SensorCustomReceiver) {
            mask.is_custom_receiver = true;
            mask.custom_receiver_data.layer.Init(ContactLayer::SensorCustomReceiver - FirstSensor);
        } else {
            mask.is_custom_receiver = false;
            mask.data.layer.Init(layer - FirstSensor);
        }
        return mask;
    }

    ContactLayer getLayer() const {
        return is_custom_receiver ? ContactLayer::SensorCustomReceiver : data.getLayer();
    }

    u32 raw;
    Data data;
    CustomReceiverData custom_receiver_data;
    util::BitField<21, 10, u32> group_handler_index;
    util::BitField<31, 1, bool, u32> is_custom_receiver;
};

/// Collision mask that is used for raycast-based queries against sensors.
union SensorQueryCollisionMask {
    constexpr explicit SensorQueryCollisionMask(u32 raw_ = 0) : raw(raw_) {}
    constexpr SensorQueryCollisionMask(const SensorQueryCollisionMask&) = default;
    constexpr SensorQueryCollisionMask& operator=(const SensorQueryCollisionMask& m) {
        raw = m.raw;
        return *this;
    }
    constexpr bool operator==(SensorQueryCollisionMask rhs) const { return raw == rhs.raw; }
    constexpr bool operator!=(SensorQueryCollisionMask rhs) const { return raw != rhs.raw; }

    util::BitField<0, NumRegularSensorLayers, u32> layer_mask;
    util::BitField<22, 10, u32> group_handler_index;
    u32 raw;
};

ContactLayerType getContactLayerType(ContactLayer layer);
u32 makeContactLayerMask(ContactLayer layer);
u32 getContactLayerBase(ContactLayerType type);
int getContactLayerBaseRelativeValue(ContactLayer layer);
const char* contactLayerToText(ContactLayer layer);
ContactLayer contactLayerFromText(const sead::SafeString& text);

const char* materialToText(Material material);
Material materialFromText(const sead::SafeString& text);

const char* groundHitToText(GroundHit hit);
GroundHit groundHitFromText(const sead::SafeString& text);

const char* floorCodeToText(FloorCode code);
FloorCode floorCodeFromText(const sead::SafeString& text);

const char* wallCodeToText(WallCode code);
WallCode wallCodeFromText(const sead::SafeString& text);

MotionType motionTypeFromText(const sead::SafeString& text);

}  // namespace ksys::phys
