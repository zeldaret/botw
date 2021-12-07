#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

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

struct ShapeParam;

struct RigidBodyParamView {
    SEAD_RTTI_BASE(RigidBodyParamView)
public:
    const char* name = "no name";
    u32 _10 = -1;
    MotionType motion_type = MotionType::Dynamic;
    float mass = 1.0f;
    sead::Vector3f inertia = sead::Vector3f::ones;
    sead::Vector3f center_of_mass = sead::Vector3f::zero;
    float linear_damping = 0.0f;
    float angular_damping = 0.05f;
    f32 _3c = 1.0f;
    f32 _40 = 1.0f;
    float max_linear_velocity = 200.0f;
    float max_angular_velocity_rad = 200.0f;
    float max_impulse = -1.0f;
    float col_impulse_scale = 1.0f;
    float friction_scale = 1.0f;
    float restitution_scale = 1.0f;
    float water_buoyancy_scale = 1.0f;
    float water_flow_effective_rate = 1.0f;
    float magne_mass_scaling_factor = 1.0f;
    bool gap68 = true;
    bool toi = false;
    bool always_character_mass_scaling = false;
    void* p = nullptr;
    ContactLayer contact_layer = ContactLayer::EntityObject;
    GroundHit groundhit = GroundHit::HitAll;
    u32 info_5e0 = 0;
    u32 contact_mask = 0;
    u32 flags = 0x80000000;
    bool ignore_normal_for_impulse = false;
    bool no_hit_ground = false;
    bool no_hit_water = false;
    bool no_char_standing_on = false;
};
KSYS_CHECK_SIZE_NX150(RigidBodyParamView, 0x90);

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
        u32 ground_hit_type_mask_val = 0;

    protected:
        void postRead_() override;
    };

    RigidBodyParam();
    ~RigidBodyParam() override;
    RigidBodyParam(const RigidBodyParam&) = delete;
    auto operator=(const RigidBodyParam&) = delete;

    bool parse(const agl::utl::ResParameterList& res_list, sead::Heap* heap);

    // TODO: types and names
    void* createRigidBody(void* x, sead::Heap* heap, bool y);
    bool getParams(RigidBodyParamView* view) const;
    void* createEntityShape(void* x, void* y, sead::Heap* heap);

    ContactLayer getContactLayer() const;
    GroundHit getGroundHit() const;
    MotionType getMotionType() const;

    Info info;
    sead::Buffer<ShapeParam> shapes;
};

}  // namespace ksys::phys
