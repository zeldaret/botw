#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterList.h>
#include <agl/utl/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

struct ShapeParamObj;
class SystemGroupHandler;
class RigidBody;

// TODO: maybe move this to NavMesh/?
enum class NavMeshType {
    NOT_USE,
    STATIC_CUTTING,
    STATIC_WALKABLE_AND_CUTTING,
    STATIC_WALKABLE_AND_CUTTING_CGO,
    STATIC_DEPENDS_ON_WALL_CODE,
    STATIC_ENEMY_ONLY,
    STATIC_NPC_ONLY,
    STATIC_LOW_CEILING,
    STATIC_GIANT_NO_ENTRY_PAINT,
    STATIC_CUTTING_CARVER,
    STATIC_AIR_WALL_FOR_HORSE,
    STATIC_FENCE_FOR_HORSE,
    STATIC_CUTTING_LARGE,
    STATIC_CURSE,
    DYNAMIC_OBSTACLE,
    DYNAMIC_SILHOUETTE_AND_OBSTACLE,
    DYNAMIC_WITHOUT_TOLERANCE,
    MATERIAL_PAINT_AND_OBSTACLE,
    MATERIAL_PAINT,
    MATERIAL_WITHOUT_TOLERANCE,
};

enum class NavMeshSubMaterial {
    LiftableByEnemy = 0xf,
    Fire = 0x10,
    Curse = 0x11,
    NPCOnly = 0x12,
    GiantNoEntry = 0x13,
    Pass = 0x14,
    None = 0x15,
};

struct RigidBodyInstanceParam {
    SEAD_RTTI_BASE(RigidBodyInstanceParam)
public:
    RigidBodyInstanceParam() = default;
    explicit RigidBodyInstanceParam(ShapeType type) : shape_type(type) {}

    const char* name = "no name";
    ShapeType shape_type = ShapeType::Unknown;
    MotionType motion_type = MotionType::Dynamic;
    float mass = 1.0f;
    sead::Vector3f inertia = sead::Vector3f::ones;
    sead::Vector3f center_of_mass = sead::Vector3f::zero;
    float linear_damping = 0.0f;
    float angular_damping = 0.05f;
    f32 gravity_factor = 1.0f;
    f32 time_factor = 1.0f;
    float max_linear_velocity = 200.0f;
    float max_angular_velocity_rad = 200.0f;
    float max_impulse = -1.0f;
    float col_impulse_scale = 1.0f;
    float friction_scale = 1.0f;
    float restitution_scale = 1.0f;
    float water_buoyancy_scale = 1.0f;
    float water_flow_effective_rate = 1.0f;
    float magne_mass_scaling_factor = 1.0f;
    bool enable_deactivation = true;
    bool toi = false;
    bool always_character_mass_scaling = false;
    SystemGroupHandler* system_group_handler = nullptr;
    ContactLayer contact_layer = ContactLayer::EntityObject;
    GroundHit groundhit = GroundHit::HitAll;
    u32 groundhit_mask = 0;
    u32 contact_mask = 0;
    SensorCollisionMask receiver_mask{SensorCollisionMask::CustomReceiverTag{}};
    bool ignore_normal_for_impulse = false;
    bool no_hit_ground = false;
    bool no_hit_water = false;
    bool no_char_standing_on = false;
    bool _90 = false;

    bool isDynamicSensor() const {
        return getContactLayerType(contact_layer) == ContactLayerType::Sensor &&
               motion_type == MotionType::Dynamic;
    }
};
KSYS_CHECK_SIZE_NX150(RigidBodyInstanceParam, 0x98);

struct RigidBodyParam : agl::utl::ParameterList {
    struct Info : agl::utl::ParameterObj {
        Info();
        ~Info() override;

        agl::utl::Parameter<sead::SafeString> rigid_body_name;
        agl::utl::Parameter<float> mass;
        agl::utl::Parameter<float> volume;
        agl::utl::Parameter<bool> toi;
        agl::utl::Parameter<bool> mEnableAutoAddWorld;
        agl::utl::Parameter<sead::SafeString> navmesh;
        agl::utl::Parameter<sead::SafeString> navmesh_sub_material;
        agl::utl::Parameter<sead::Vector3f> inertia;
        agl::utl::Parameter<sead::Vector3f> center_of_mass;
        agl::utl::Parameter<sead::Vector3f> bounding_center;
        agl::utl::Parameter<sead::Vector3f> bounding_extents;
        agl::utl::Parameter<sead::SafeString> contact_point_info;
        agl::utl::Parameter<sead::SafeString> collision_info;
        agl::utl::Parameter<float> max_linear_velocity;
        agl::utl::Parameter<float> linear_damping;
        agl::utl::Parameter<float> max_angular_velocity_rad;
        agl::utl::Parameter<float> angular_damping;
        agl::utl::Parameter<float> max_impulse;
        agl::utl::Parameter<float> col_impulse_scale;
        agl::utl::Parameter<bool> ignore_normal_for_impulse;
        agl::utl::Parameter<bool> always_character_mass_scaling;
        agl::utl::Parameter<float> friction_scale;
        agl::utl::Parameter<float> restitution_scale;
        agl::utl::Parameter<float> water_buoyancy_scale;
        agl::utl::Parameter<float> water_flow_effective_rate;
        agl::utl::Parameter<float> magne_mass_scaling_factor;
        agl::utl::Parameter<sead::SafeString> motion_type;
        agl::utl::Parameter<sead::SafeString> layer;
        agl::utl::Parameter<sead::SafeString> groundhit;
        agl::utl::Parameter<bool> use_ground_hit_type_mask;
        agl::utl::Parameter<sead::SafeString> ground_hit_type_mask;
        agl::utl::Parameter<sead::SafeString> receiver_type;
        agl::utl::Parameter<bool> no_hit_ground;
        agl::utl::Parameter<bool> no_hit_water;
        agl::utl::Parameter<bool> no_char_standing_on;
        agl::utl::Parameter<u32> contact_mask;
        agl::utl::Parameter<sead::SafeString> link_matrix;
        agl::utl::Parameter<sead::SafeString> link_entity_set;
        agl::utl::Parameter<sead::SafeString> link_entity_body;
        agl::utl::Parameter<bool> use_entity_shape;
        agl::utl::Parameter<int> shape_num;
        NavMeshType navmesh_val = NavMeshType::NOT_USE;
        NavMeshSubMaterial navmesh_sub_material_val = NavMeshSubMaterial::None;
        u32 ground_hit_mask = 0;

    protected:
        void postRead_() override;
    };

    enum class CreateFixedBoxWithNoCollision : bool {
        Yes = true,
        No = false,
    };

    RigidBodyParam();
    ~RigidBodyParam() override;
    RigidBodyParam(const RigidBodyParam&) = delete;
    auto operator=(const RigidBodyParam&) = delete;

    bool parse(const agl::utl::ResParameterList& res_list, sead::Heap* heap);

    void makeInstanceParam(RigidBodyInstanceParam* param) const;

    RigidBody* createRigidBody(
        SystemGroupHandler* group_handler, sead::Heap* heap,
        CreateFixedBoxWithNoCollision no_collision = CreateFixedBoxWithNoCollision::No) const;

    /// @param linked_body Must be a RigidBodyFromShape.
    RigidBody* createEntityShapeBody(RigidBody* linked_body, SystemGroupHandler* group_handler,
                                     sead::Heap* heap) const;

    ContactLayer getContactLayer() const;
    GroundHit getGroundHit() const;
    MotionType getMotionType() const;
    ShapeType getShapeType() const;

    Info info;
    sead::Buffer<ShapeParamObj> shapes;
};

}  // namespace ksys::phys
