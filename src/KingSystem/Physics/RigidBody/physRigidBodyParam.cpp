#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/System/physShapeParam.h"

namespace ksys::phys {

RigidBodyParam::RigidBodyParam() = default;

RigidBodyParam::~RigidBodyParam() = default;

RigidBodyParam::Info::Info()
    : rigid_body_name("RigidBody", "rigid_body_name", this), mass(1.0, "mass", this),
      volume(0.0, "volume", this), toi(false, "toi", this),
      mEnableAutoAddWorld(false, "mEnableAutoAddWorld", this), navmesh("NOT_USE", "navmesh", this),
      navmesh_sub_material("Others", "navmesh_sub_material", this),
      inertia(sead::Vector3f::ones, "inertia", this),
      center_of_mass(sead::Vector3f::zero, "center_of_mass", this),
      bounding_center(sead::Vector3f::zero, "bounding_center", this),
      bounding_extents(sead::Vector3f::zero, "bounding_extents", this),
      contact_point_info(sead::SafeString::cEmptyString, "contact_point_info", this),
      collision_info(sead::SafeString::cEmptyString, "collision_info", this),
      max_linear_velocity(200.0, "max_linear_velocity", this),
      linear_damping(0.0, "linear_damping", this),
      max_angular_velocity_rad(200.0, "max_angular_velocity_rad", this),
      angular_damping(0.05, "angular_damping", this), max_impulse(-1.0, "max_impulse", this),
      col_impulse_scale(1.0, "col_impulse_scale", this),
      ignore_normal_for_impulse(false, "ignore_normal_for_impulse", this),
      always_character_mass_scaling(false, "always_character_mass_scaling", this),
      friction_scale(1.0, "friction_scale", this),
      restitution_scale(1.0, "restitution_scale", this),
      water_buoyancy_scale(1.0, "water_buoyancy_scale", this),
      water_flow_effective_rate(1.0, "water_flow_effective_rate", this),
      magne_mass_scaling_factor(1.0, "magne_mass_scaling_factor", this),
      motion_type("Fixed", "motion_type", this),
      layer(sead::SafeString::cEmptyString, "layer", this),
      groundhit(sead::SafeString::cEmptyString, "groundhit", this),
      use_ground_hit_type_mask(false, "use_ground_hit_type_mask", this),
      ground_hit_type_mask(sead::SafeString::cEmptyString, "ground_hit_type_mask", this),
      receiver_type(sead::SafeString::cEmptyString, "receiver_type", this),
      no_hit_ground(false, "no_hit_ground", this), no_hit_water(false, "no_hit_water", this),
      no_char_standing_on(false, "no_char_standing_on", this),
      contact_mask(0, "contact_mask", this),
      link_matrix(sead::SafeString::cEmptyString, "link_matrix", this),
      link_entity_set(sead::SafeString::cEmptyString, "link_entity_set", this),
      link_entity_body(sead::SafeString::cEmptyString, "link_entity_body", this),
      use_entity_shape(false, "use_entity_shape", this), shape_num(0, "shape_num", this) {}

RigidBodyParam::Info::~Info() = default;

bool RigidBodyParam::parse(const agl::utl::ResParameterList& res_list, sead::Heap* heap) {
    if (!res_list)
        return false;

    info.applyResParameterObj(res_list.getResParameterObj(0));

    const int num_shapes = info.shape_num.ref();
    if (num_shapes < 1)
        return true;

    shapes.allocBufferAssert(num_shapes, heap);
    for (int i = 0; i < num_shapes; ++i) {
        if (!shapes[i].parse(res_list.getResParameterObj(i + 1), heap))
            return false;
    }

    return true;
}

ContactLayer RigidBodyParam::getContactLayer() const {
    return contactLayerFromText(*info.layer);
}

GroundHit RigidBodyParam::getGroundHit() const {
    return groundHitFromText(*info.groundhit);
}

MotionType RigidBodyParam::getMotionType() const {
    return motionTypeFromText(*info.motion_type);
}

// TODO: move this to another translation unit (figure out where this belongs)
[[gnu::noinline]] static u32 orGroundHitTypeMask(u32 mask, const sead::SafeString& type) {
    mask |= (0x100 << groundHitFromText(type)) & 0xffff00;
    return mask;
}

namespace {
constexpr const char* navmesh_types[] = {
    "NOT_USE",
    "STATIC_CUTTING",
    "STATIC_WALKABLE_AND_CUTTING",
    "STATIC_WALKABLE_AND_CUTTING_CGO",
    "STATIC_DEPENDS_ON_WALL_CODE",
    "STATIC_ENEMY_ONLY",
    "STATIC_NPC_ONLY",
    "STATIC_LOW_CEILING",
    "STATIC_GIANT_NO_ENTRY_PAINT",
    "STATIC_CUTTING_CARVER",
    "STATIC_AIR_WALL_FOR_HORSE",
    "STATIC_FENCE_FOR_HORSE",
    "STATIC_CUTTING_LARGE",
    "STATIC_CURSE",
    "DYNAMIC_OBSTACLE",
    "DYNAMIC_SILHOUETTE_AND_OBSTACLE",
    "DYNAMIC_WITHOUT_TOLERANCE",
    "MATERIAL_PAINT_AND_OBSTACLE",
    "MATERIAL_PAINT",
    "MATERIAL_WITHOUT_TOLERANCE",
};

struct NavMeshSubMaterialInfo {
    sead::SafeString name;
    NavMeshSubMaterial value;
};
}  // namespace

void RigidBodyParam::Info::postRead_() {
    for (int i = 0; i < int(std::size(navmesh_types)); ++i) {
        if (*navmesh == navmesh_types[i]) {
            navmesh_val = NavMeshType(i);
            break;
        }
    }

    navmesh_sub_material_val = NavMeshSubMaterial::None;
    const NavMeshSubMaterialInfo sub_material_info[] = {
        {"LiftableByEnemy", NavMeshSubMaterial::LiftableByEnemy},
        {"Fire", NavMeshSubMaterial::Fire},
        {"Curse", NavMeshSubMaterial::Curse},
        {"NPCOnly", NavMeshSubMaterial::NPCOnly},
        {"GiantNoEntry", NavMeshSubMaterial::GiantNoEntry},
        {"Pass", NavMeshSubMaterial::Pass},
    };
    for (int i = 0; i < int(std::size(sub_material_info)); ++i) {
        if (*navmesh_sub_material == sub_material_info[i].name) {
            navmesh_sub_material_val = sub_material_info[i].value;
            break;
        }
    }

    if (*use_ground_hit_type_mask && !ground_hit_type_mask->isEmpty()) {
        ground_hit_type_mask_val = 0;

        sead::FixedSafeString<64> type_str;
        auto it = ground_hit_type_mask->tokenBegin(",");
        const auto end = ground_hit_type_mask->tokenEnd(",");
        while (end != it) {
            it.getAndForward(&type_str);
            if (!type_str.isEmpty())
                ground_hit_type_mask_val = orGroundHitTypeMask(ground_hit_type_mask_val, type_str);
        }
    } else {
        ground_hit_type_mask_val = 0;
    }
}

}  // namespace ksys::phys
