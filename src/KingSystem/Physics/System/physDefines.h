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

union ReceiverMask {
    union Data {
        util::BitField<0, 5, u32> layer;
        // TODO: rename once we figure out what this layer is used for
        util::BitField<5, 1, bool, u32> has_layer2;
        util::BitField<6, 5, u32> layer2;
    };

    union CustomReceiverData {
        util::BitField<0, 21, u32> layer;
        util::BitField<21, 10, u32> group_handler_index;
    };

    constexpr ReceiverMask() : raw(0) { is_custom_receiver = true; }
    constexpr explicit ReceiverMask(u32 raw_) : raw(raw_) {}
    constexpr ReceiverMask(const ReceiverMask&) = default;
    constexpr ReceiverMask& operator=(const ReceiverMask& m) {
        raw = m.raw;
        return *this;
    }

    static ReceiverMask make(ContactLayer layer) {
        ReceiverMask mask;
        if (layer == ContactLayer::SensorCustomReceiver) {
            mask.is_custom_receiver = true;
            mask.custom_receiver_data.layer.Init(ContactLayer::SensorCustomReceiver - FirstSensor);
        } else {
            mask.is_custom_receiver = false;
            mask.data.layer.Init(layer - FirstSensor);
        }
        return mask;
    }

    u32 raw;
    Data data;
    CustomReceiverData custom_receiver_data;
    // FIXME: is this a sensor layer mask?
    util::BitField<0, 21, u32> layer_mask;
    util::BitField<31, 1, bool, u32> is_custom_receiver;
};

union EntityCollisionFilterInfo {
    union Data {
        ContactLayer getLayer() const { return int(layer); }
        ContactLayer getLayerSensor() const { return int(layer + FirstSensor); }
        GroundHit getGroundHit() const { return int(ground_hit); }

        u32 raw;
        util::BitField<0, 5, u32> layer;
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
        util::BitField<24, 1, u32> unk24;
        util::BitField<25, 5, u32> layer;
    };

    constexpr explicit EntityCollisionFilterInfo(u32 raw_ = 0) : raw(raw_) {}
    constexpr EntityCollisionFilterInfo(const EntityCollisionFilterInfo&) = default;
    constexpr EntityCollisionFilterInfo& operator=(const EntityCollisionFilterInfo& m) {
        raw = m.raw;
        return *this;
    }

    bool operator==(EntityCollisionFilterInfo rhs) const { return raw == rhs.raw; }
    bool operator!=(EntityCollisionFilterInfo rhs) const { return raw != rhs.raw; }

    static EntityCollisionFilterInfo make(ContactLayer layer, GroundHit ground_hit) {
        EntityCollisionFilterInfo mask;
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
    util::BitField<5, 1, bool, u32> unk5;
    /// Whether ground collision is disabled.
    util::BitField<6, 1, bool, u32> no_ground_collision;
    /// Whether water collision is disabled.
    util::BitField<7, 1, bool, u32> no_water_collision;
    util::BitField<30, 1, bool, u32> unk30;
    util::BitField<31, 1, bool, u32> is_ground_hit_mask;
};
static_assert(sizeof(EntityCollisionFilterInfo) == sizeof(u32));

ContactLayerType getContactLayerType(ContactLayer layer);
u32 makeContactLayerMask(ContactLayer layer);
u32 getContactLayerBase(ContactLayerType type);
u32 getContactLayerBaseRelativeValue(ContactLayer layer);
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
