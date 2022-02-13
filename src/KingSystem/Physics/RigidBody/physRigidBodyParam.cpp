#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include <basis/seadRawPrint.h>
#include <functional>
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/BoxWater/physBoxWaterRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/BoxWater/physBoxWaterShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/Shape/CylinderWater/physCylinderWaterRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/CylinderWater/physCylinderWaterShape.h"
#include "KingSystem/Physics/RigidBody/Shape/List/physListShape.h"
#include "KingSystem/Physics/RigidBody/Shape/List/physListShapeRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physShapeParamObj.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include "KingSystem/Utils/SafeDelete.h"

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

void RigidBodyParam::makeInstanceParam(RigidBodyInstanceParam* param) const {
    param->mass = *info.mass;
    param->name = info.rigid_body_name->cstr();
    param->inertia = *info.inertia;
    param->center_of_mass = *info.center_of_mass;
    param->max_linear_velocity = *info.max_linear_velocity;
    param->max_angular_velocity_rad = *info.max_angular_velocity_rad;
    param->toi = *info.toi;
    param->motion_type = getMotionType();
    param->linear_damping = *info.linear_damping;
    param->angular_damping = *info.angular_damping;
    param->max_impulse = *info.max_impulse;
    param->col_impulse_scale = *info.col_impulse_scale;
    param->ignore_normal_for_impulse = *info.ignore_normal_for_impulse;
    param->always_character_mass_scaling = *info.always_character_mass_scaling;
    param->friction_scale = *info.friction_scale;
    param->restitution_scale = *info.restitution_scale;
    param->water_buoyancy_scale = *info.water_buoyancy_scale;
    param->water_flow_effective_rate = *info.water_flow_effective_rate;
    param->magne_mass_scaling_factor = *info.magne_mass_scaling_factor;
    param->contact_layer = getContactLayer();
    param->groundhit = getGroundHit();
    param->groundhit_mask = info.ground_hit_mask;
    param->contact_mask = *info.contact_mask;
    param->no_hit_ground = *info.no_hit_ground;
    param->no_hit_water = *info.no_hit_water;
    param->no_char_standing_on = *info.no_char_standing_on;
    receiverMaskGetSensorLayerMaskForType(&param->receiver_mask, *info.receiver_type);
}

template <auto Getter, typename ParamT>
static bool makeParamImpl(const RigidBodyParam& param, RigidBodyInstanceParam* out,
                          ShapeType shape_type) {
    if (param.getShapeType() != shape_type)
        return false;

    param.makeInstanceParam(out);
    std::invoke(Getter, param.shapes[0], static_cast<ParamT*>(out));
    return true;
}

template <auto Getter, typename ParamT>
static bool makeParam(const RigidBodyParam& param, ParamT* out, ShapeType shape_type) {
    return makeParamImpl<Getter, ParamT>(param, out, shape_type);
}

static bool makeSphereParam(const RigidBodyParam& param, SphereParam* out) {
    return makeParam<&ShapeParamObj::getSphere>(param, out, ShapeType::Sphere);
}

static bool makeCapsuleParam(const RigidBodyParam& param, CapsuleParam* out) {
    return makeParam<&ShapeParamObj::getCapsule>(param, out, ShapeType::Capsule);
}

static bool makeBoxParam(const RigidBodyParam& param, BoxParam* out) {
    return makeParam<&ShapeParamObj::getBox>(param, out, ShapeType::Box);
}

static bool makeCylinderParam(const RigidBodyParam& param, CylinderParam* out) {
    return makeParam<&ShapeParamObj::getCylinder>(param, out, ShapeType::Cylinder);
}

static bool makePolytopeParam(const RigidBodyParam& param, PolytopeParam* out) {
    return makeParam<&ShapeParamObj::getPolytope>(param, out, ShapeType::Polytope);
}

RigidBody*
RigidBodyParam::createRigidBody(SystemGroupHandler* group_handler, sead::Heap* heap,
                                RigidBodyParam::CreateFixedBoxWithNoCollision no_collision) const {
    if (no_collision == CreateFixedBoxWithNoCollision::Yes) {
        BoxParam param;
        makeInstanceParam(&param);

        if (getContactLayerType(param.contact_layer) == ContactLayerType::Entity)
            param.contact_layer = ContactLayer::EntityNoHit;
        else
            param.contact_layer = ContactLayer::SensorNoHit;

        param.motion_type = MotionType::Fixed;
        param.translate = *info.bounding_center;
        param.extents = *info.bounding_extents;
        param.system_group_handler = group_handler;
        auto* body = BoxRigidBody::make(&param, heap);
        body->setFlag20();
        return body;
    }

    const int num_shapes = *info.shape_num;

    if (num_shapes == 1) {
        switch (getShapeType()) {
        case ShapeType::Sphere: {
            SphereParam param;
            makeSphereParam(*this, &param);
            param.system_group_handler = group_handler;
            return SphereRigidBody::make(&param, heap);
        }

        case ShapeType::Capsule: {
            CapsuleParam param;
            makeCapsuleParam(*this, &param);
            param.system_group_handler = group_handler;
            return CapsuleRigidBody::make(&param, heap);
        }

        case ShapeType::Box: {
            BoxParam param;
            makeBoxParam(*this, &param);
            param.system_group_handler = group_handler;
            if (param.contact_layer == ContactLayer::EntityWater)
                return BoxWaterRigidBody::make(&param, heap);
            return BoxRigidBody::make(&param, heap);
        }

        case ShapeType::Cylinder: {
            CylinderParam param;
            makeCylinderParam(*this, &param);
            param.system_group_handler = group_handler;
            if (param.contact_layer == ContactLayer::EntityWater)
                return CylinderWaterRigidBody::make(&param, heap);
            return CylinderRigidBody::make(&param, heap);
        }

        case ShapeType::Polytope: {
            PolytopeParam param;
            makePolytopeParam(*this, &param);
            param.system_group_handler = group_handler;

            auto* body = PolytopeRigidBody::make(&param, heap);
            for (int i = 0, n = *shapes[0].vertex_num; i < n; ++i)
                body->setVertex(i, *shapes[0].vertices[i]);

            body->setVolume(*info.volume);
            body->updateShape();
            return body;
        }

        case ShapeType::List:
        case ShapeType::CharacterPrism:
        case ShapeType::BoxWater:
        case ShapeType::CylinderWater:
        case ShapeType::Unknown:
            break;
        }
        SEAD_ASSERT_MSG(false, "unexpected shape type (shape_num=1)");
        return nullptr;
    }

    // Multiple shapes. Use a ListShape.

    ListShapeRigidBodyParam list_param;
    makeInstanceParam(&list_param);
    list_param.system_group_handler = group_handler;
    list_param.num_shapes = num_shapes;

    auto* list_body = ListShapeRigidBody::make(&list_param, heap);
    list_body->setUpdateRequestedFlag();

    for (int i = 0; i < num_shapes; ++i) {
        switch (shapes[i].getShapeType()) {
        case ShapeType::Sphere: {
            SphereShapeParam param;
            shapes[i].getSphere(&param);
            list_body->replaceWithNewSphere(i, param, heap);
            continue;
        }

        case ShapeType::Capsule: {
            CapsuleShapeParam param;
            shapes[i].getCapsule(&param);
            list_body->replaceWithNewCapsule(i, param, heap);
            continue;
        }

        case ShapeType::Box: {
            BoxShapeParam param;
            shapes[i].getBox(&param);
            list_body->replaceWithNewBox(i, param, heap);
            continue;
        }

        case ShapeType::Cylinder: {
            CylinderShapeParam param;
            shapes[i].getCylinder(&param);
            list_body->replaceWithNewCylinder(i, param, heap);
            continue;
        }

        case ShapeType::Polytope: {
            PolytopeShapeParam param;
            shapes[i].getPolytope(&param);
            auto* polytope =
                static_cast<PolytopeShape*>(list_body->replaceWithNewPolytope(i, param, heap));
            for (int vertex_idx = 0, n = *shapes[i].vertex_num; vertex_idx < n; ++vertex_idx)
                polytope->setVertex(vertex_idx, *shapes[i].vertices[vertex_idx]);
            continue;
        }

        case ShapeType::List:
        case ShapeType::CharacterPrism:
        case ShapeType::BoxWater:
        case ShapeType::CylinderWater:
        case ShapeType::Unknown:
            break;
        }
        SEAD_ASSERT_MSG(false, "unexpected shape type for list shape");
        util::safeDelete(list_body);
    }

    if (!list_body)
        return nullptr;

    list_body->updateShape();
    list_body->processUpdateRequests();
    return list_body;
}

RigidBody* RigidBodyParam::createEntityShapeBody(RigidBody* linked_body,
                                                 SystemGroupHandler* group_handler,
                                                 sead::Heap* heap) const {
    auto* linked_shape_body = sead::DynamicCast<RigidBodyFromShape>(linked_body);
    if (!linked_shape_body)
        return nullptr;

    auto* body = RigidBodyFromShape::createEntityShapeBody(*info.rigid_body_name, getContactLayer(),
                                                           linked_shape_body, heap, group_handler);
    if (!body)
        return nullptr;

    body->setUpdateRequestedFlag();
    body->setMaxLinearVelocity(*info.max_linear_velocity);
    body->setMaxAngularVelocity(*info.max_angular_velocity_rad);
    body->setCenterOfMassInLocal(*info.center_of_mass);
    body->updateCollidableQualityType(*info.toi);
    body->processUpdateRequests();

    return body;
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

ShapeType RigidBodyParam::getShapeType() const {
    if (*info.shape_num > 1)
        return ShapeType::List;

    return shapes[0].getShapeType();
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
        ground_hit_mask = 0;

        sead::FixedSafeString<64> type_str;
        auto it = ground_hit_type_mask->tokenBegin(",");
        const auto end = ground_hit_type_mask->tokenEnd(",");
        while (end != it) {
            it.getAndForward(&type_str);
            if (!type_str.isEmpty())
                ground_hit_mask = orEntityGroundHitMask(ground_hit_mask, type_str);
        }
    } else {
        ground_hit_mask = 0;
    }
}

}  // namespace ksys::phys
