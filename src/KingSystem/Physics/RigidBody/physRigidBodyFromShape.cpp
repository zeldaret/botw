#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBodyCinfo.h>
#include <basis/seadRawPrint.h>
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/BoxWater/physBoxWaterRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/BoxWater/physBoxWaterShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/CharacterPrism/physCharacterPrismShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/CylinderWater/physCylinderWaterRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/CylinderWater/physCylinderWaterShape.h"
#include "KingSystem/Physics/RigidBody/Shape/List/physListShape.h"
#include "KingSystem/Physics/RigidBody/Shape/List/physListShapeRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

SphereRigidBody* RigidBodyFromShape::createSphere(RigidBodyInstanceParam* param, sead::Heap* heap) {
    return make<SphereRigidBody, SphereShape, SphereParam>(param, heap);
}

CapsuleRigidBody* RigidBodyFromShape::createCapsule(RigidBodyInstanceParam* param,
                                                    sead::Heap* heap) {
    return make<CapsuleRigidBody, CapsuleShape, CapsuleParam>(param, heap);
}

CylinderRigidBody* RigidBodyFromShape::createCylinder(RigidBodyInstanceParam* param,
                                                      sead::Heap* heap) {
    return make<CylinderRigidBody, CylinderShape, CylinderParam>(param, heap);
}

CylinderWaterRigidBody* RigidBodyFromShape::createCylinderWater(RigidBodyInstanceParam* param,
                                                                sead::Heap* heap) {
    return make<CylinderWaterRigidBody, CylinderWaterShape, CylinderParam>(param, heap);
}

BoxRigidBody* RigidBodyFromShape::createBox(RigidBodyInstanceParam* param, sead::Heap* heap) {
    return make<BoxRigidBody, BoxShape, BoxParam>(param, heap);
}

BoxWaterRigidBody* RigidBodyFromShape::createBoxWater(RigidBodyInstanceParam* param,
                                                      sead::Heap* heap) {
    return make<BoxWaterRigidBody, BoxWaterShape, BoxParam>(param, heap);
}

PolytopeRigidBody* RigidBodyFromShape::createPolytope(RigidBodyInstanceParam* param,
                                                      sead::Heap* heap) {
    return make<PolytopeRigidBody, PolytopeShape, PolytopeParam>(param, heap);
}

ListShapeRigidBody* RigidBodyFromShape::createList(RigidBodyInstanceParam* param,
                                                   sead::Heap* heap) {
    return make<ListShapeRigidBody, ListShape, ListShapeRigidBodyParam>(param, heap);
}

RigidBody* RigidBodyFromShape::clone(sead::Heap* heap, SystemGroupHandler* group_handler) const {
    switch (getShapeType()) {
    case ShapeType::Sphere:
        return cloneImpl<SphereRigidBody, SphereShape, SphereParam>(heap, group_handler);
    case ShapeType::Capsule:
        return cloneImpl<CapsuleRigidBody, CapsuleShape, CapsuleParam>(heap, group_handler);
    case ShapeType::Cylinder:
        return cloneImpl<CylinderRigidBody, CylinderShape, CylinderParam>(heap, group_handler);
    case ShapeType::CylinderWater:
        return cloneImpl<CylinderWaterRigidBody, CylinderWaterShape, CylinderParam>(heap,
                                                                                    group_handler);
    case ShapeType::Box:
        return cloneImpl<BoxRigidBody, BoxShape, BoxParam>(heap, group_handler);
    case ShapeType::BoxWater:
        return cloneImpl<BoxWaterRigidBody, BoxWaterShape, BoxParam>(heap, group_handler);
    case ShapeType::Polytope:
        return cloneImpl<PolytopeRigidBody, PolytopeShape, PolytopeParam>(heap, group_handler);
    case ShapeType::List:
        return cloneImpl<ListShapeRigidBody, ListShape, ListShapeRigidBodyParam>(heap,
                                                                                 group_handler);
    case ShapeType::CharacterPrism:
    case ShapeType::Unknown:
        break;
    }
    return nullptr;
}

RigidBody* RigidBodyFromShape::create(const Shape& shape, RigidBodyInstanceParam* param,
                                      sead::Heap* heap, const SystemGroupHandler* group_handler) {
    switch (shape.getType()) {
    case ShapeType::Sphere:
        return make<SphereRigidBody, SphereShape>(shape, param, heap, group_handler);
    case ShapeType::Capsule:
        return make<CapsuleRigidBody, CapsuleShape>(shape, param, heap, group_handler);
    case ShapeType::Cylinder:
        return make<CylinderRigidBody, CylinderShape>(shape, param, heap, group_handler);
    case ShapeType::CylinderWater:
        return make<CylinderWaterRigidBody, CylinderWaterShape>(shape, param, heap, group_handler);
    case ShapeType::Box:
        return make<BoxRigidBody, BoxShape>(shape, param, heap, group_handler);
    case ShapeType::BoxWater:
        return make<BoxWaterRigidBody, BoxWaterShape>(shape, param, heap, group_handler);
    case ShapeType::Polytope:
        return make<PolytopeRigidBody, PolytopeShape>(shape, param, heap, group_handler);
    case ShapeType::List:
        return make<ListShapeRigidBody, ListShape>(shape, param, heap, group_handler);
    case ShapeType::CharacterPrism: {
        auto* prism = sead::DynamicCast<const CharacterPrismShape>(&shape);
        if (!prism || !prism->getUnderlyingShape())
            break;
        return make<PolytopeRigidBody, PolytopeShape>(*prism->getUnderlyingShape(), param, heap,
                                                      group_handler);
    }
    case ShapeType::Unknown:
        break;
    }
    return nullptr;
}

RigidBody* RigidBodyFromShape::createEntityShapeBody(const sead::SafeString& name,
                                                     ContactLayer layer,
                                                     RigidBodyFromShape* linked_body,
                                                     sead::Heap* heap,
                                                     SystemGroupHandler* group_handler) {
    switch (linked_body->getShapeType()) {
    case ShapeType::Sphere:
        return createEntityShapeBodyImpl<SphereRigidBody, SphereShape, SphereParam>(
            name, layer, linked_body, heap, group_handler);
    case ShapeType::Capsule:
        return createEntityShapeBodyImpl<CapsuleRigidBody, CapsuleShape, CapsuleParam>(
            name, layer, linked_body, heap, group_handler);
    case ShapeType::Cylinder:
        return createEntityShapeBodyImpl<CylinderRigidBody, CylinderShape, CylinderParam>(
            name, layer, linked_body, heap, group_handler);
    case ShapeType::CylinderWater:
        return createEntityShapeBodyImpl<CylinderWaterRigidBody, CylinderWaterShape, CylinderParam>(
            name, layer, linked_body, heap, group_handler);
    case ShapeType::Box:
        return createEntityShapeBodyImpl<BoxRigidBody, BoxShape, BoxParam>(name, layer, linked_body,
                                                                           heap, group_handler);
    case ShapeType::BoxWater:
        break;
    case ShapeType::Polytope:
        return createEntityShapeBodyImpl<PolytopeRigidBody, PolytopeShape, PolytopeParam>(
            name, layer, linked_body, heap, group_handler);
    case ShapeType::List:
        return createEntityShapeBodyImpl<ListShapeRigidBody, ListShape, ListShapeRigidBodyParam>(
            name, layer, linked_body, heap, group_handler);
    case ShapeType::CharacterPrism:
    case ShapeType::Unknown:
        break;
    }
    return nullptr;
}

RigidBodyFromShape::RigidBodyFromShape(hkpRigidBody* hkp_rigid_body, ContactLayerType layer_type,
                                       const sead::SafeString& name, bool set_flag_10,
                                       sead::Heap* heap)
    : RigidBody(RigidBody::Type::FromShape, layer_type, hkp_rigid_body, name, heap, set_flag_10) {}

RigidBodyFromShape::~RigidBodyFromShape() {
    mHkBody->setName(nullptr);
    mHkBody->deallocateInternalArrays();
    /// @bug This should be `delete mhkBody;` -- hkpRigidBody is not trivially destructible and
    /// calling operator delete directly does not call the destructor.
    if (mHkBody)
        operator delete(mHkBody);
}

ShapeType RigidBodyFromShape::getShapeType() const {
    return getShape_()->getType();
}

const MaterialMask* RigidBodyFromShape::tryGetMaterialMask() const {
    switch (getShape_()->getType()) {
    case ShapeType::Sphere:
        return &sead::DynamicCast<const SphereRigidBody>(this)->getMaterialMask();
    case ShapeType::Capsule:
        return &sead::DynamicCast<const CapsuleRigidBody>(this)->getMaterialMask();
    case ShapeType::Box:
        return &sead::DynamicCast<const BoxRigidBody>(this)->getMaterialMask();
    case ShapeType::Cylinder:
        return &sead::DynamicCast<const CylinderRigidBody>(this)->getMaterialMask();
    case ShapeType::Polytope:
        return &sead::DynamicCast<const PolytopeRigidBody>(this)->getMaterialMask();
    case ShapeType::List:
        return &sead::DynamicCast<const ListShapeRigidBody>(this)->getMaterialMask(0);
    case ShapeType::BoxWater:
        return &sead::DynamicCast<const BoxWaterRigidBody>(this)->getMaterialMask();
    case ShapeType::CylinderWater:
        return &sead::DynamicCast<const CylinderWaterRigidBody>(this)->getMaterialMask();
    case ShapeType::CharacterPrism:
    case ShapeType::Unknown:
        SEAD_ASSERT_MSG(false, "unexpected shape type");
        break;
    }
    return &sead::DynamicCast<const SphereRigidBody>(this)->getMaterialMask();
}

const hkpShape* RigidBodyFromShape::getNewHavokShape_() {
    return getShape_()->updateHavokShape();
}

float RigidBodyFromShape::updateScale_(float scale, float old_scale) {
    if (scale == old_scale)
        return old_scale;

    // Relative scale.
    const float ratio = scale / old_scale;

    getShape_()->setScale(ratio);
    updateShape();

    setCenterOfMassInLocal(getCenterOfMassInLocal() * ratio);

    if (isEntity()) {
        const float scale3 = ratio * ratio * ratio;
        setMass(getMass() * scale3);

        const float scale5 = scale3 * ratio * ratio;
        setInertiaLocal(getInertiaLocal() * scale5);
    }

    return scale;
}

template <typename RigidBodyT, typename ShapeT, typename ParamType>
RigidBodyT* RigidBodyFromShape::make(RigidBodyInstanceParam* param, sead::Heap* heap) {
    if (param->isDynamicSensor())
        param->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<ParamType>(param);
    auto* shape = ShapeT::make(*v, heap);
    return make<RigidBodyT>(shape, true, *param, heap);
}

template <typename RigidBodyT, typename ShapeT>
RigidBodyT* RigidBodyFromShape::make(ShapeT* shape, bool set_flag_10,
                                     const RigidBodyInstanceParam& param, sead::Heap* heap) {
    const auto layer_type = getContactLayerType(param.contact_layer);

    hkMatrix3 inertia_mtx;
    const auto inertia = toHkVec4(param.inertia);
    inertia_mtx.m_col0.setMul(inertia, hkVector4f::getConstant<HK_QUADREAL_1000>());
    inertia_mtx.m_col1.setMul(inertia, hkVector4f::getConstant<HK_QUADREAL_0100>());
    inertia_mtx.m_col2.setMul(inertia, hkVector4f::getConstant<HK_QUADREAL_0010>());

    // Set up construction info for the Havok rigid body.
    hkpRigidBodyCinfo cinfo;
    cinfo.m_shape = shape->getHavokShapeConst();
    cinfo.m_centerOfMass = toHkVec4(param.center_of_mass);
    cinfo.m_mass = param.mass;
    cinfo.m_inertiaTensor = inertia_mtx;
    cinfo.m_linearDamping = param.linear_damping;
    cinfo.m_angularDamping = param.angular_damping;
    cinfo.m_gravityFactor = param.gravity_factor;
    cinfo.m_timeFactor = param.time_factor;
    cinfo.m_maxLinearVelocity = param.max_linear_velocity;
    cinfo.m_maxAngularVelocity = param.max_angular_velocity_rad;
    cinfo.m_enableDeactivation = param.enable_deactivation;
    cinfo.m_numShapeKeysInContactPointProperties = -1;

    switch (param.motion_type) {
    case MotionType::Dynamic:
        cinfo.m_motionType = hkpMotion::MOTION_DYNAMIC;
        break;
    case MotionType::Fixed:
        cinfo.m_motionType = hkpMotion::MOTION_FIXED;
        break;
    case MotionType::Keyframed:
        cinfo.m_motionType = hkpMotion::MOTION_KEYFRAMED;
        break;
    case MotionType::Unknown:
    case MotionType::Invalid:
        break;
    }

    void* hk_body_storage = util::allocStorage<hkpRigidBody>(heap);
    if (!hk_body_storage)
        return nullptr;

    auto* hk_body = new (hk_body_storage) hkpRigidBody(cinfo);

    RigidBodyFromShape* body =
        new (heap) RigidBodyT(hk_body, shape, layer_type, param.name, set_flag_10, heap);

    body->mFlags.set(Flag::UpdateRequested);

    if (param.motion_type == MotionType::Keyframed) {
        hk_body->setCenterOfMassLocal(cinfo.m_centerOfMass);
        hk_body->setMaxLinearVelocity(cinfo.m_maxLinearVelocity);
        hk_body->setMaxAngularVelocity(cinfo.m_maxAngularVelocity);
    }

    if (param._90) {
        body->setFlag20();
    } else if (!body->initMotionAccessor(param, heap, false)) {
        delete body;
        return nullptr;
    }

    if (param.contact_layer == ContactLayer::SensorCustomReceiver) {
        body->setSensorCustomReceiver(param.receiver_mask, param.system_group_handler);
    } else if (param.groundhit_mask != 0) {
        body->setGroundHitMask(param.contact_layer, param.groundhit_mask);
    } else {
        body->setContactLayerAndGroundHitAndHandler(param.contact_layer, param.groundhit,
                                                    param.system_group_handler);
    }

    body->updateCollidableQualityType(param.toi);
    body->updateShape();
    body->clearEntityMotionFlag20(!param.ignore_normal_for_impulse);
    body->enableGroundCollision(!param.no_hit_ground);
    body->enableWaterCollision(!param.no_hit_water);
    body->mFlags.change(Flag::NoCharStandingOn, param.no_char_standing_on);
    body->setContactMask(param.contact_mask);
    body->setEntityMotionFlag1(param.always_character_mass_scaling);
    body->processUpdateRequests(nullptr, nullptr);

    return static_cast<RigidBodyT*>(body);
}

template <typename RigidBodyT, typename ShapeT>
RigidBodyT* RigidBodyFromShape::make(const Shape& shape, RigidBodyInstanceParam* param,
                                     sead::Heap* heap, const SystemGroupHandler* group_handler) {
    auto* derived_shape = sead::DynamicCast<const ShapeT>(&shape);
    auto* cloned_shape = derived_shape->clone(heap);

    RigidBody* body = make<RigidBodyT, ShapeT>(cloned_shape, true, *param, heap);

    body->setUpdateRequestedFlag();

    u32 collision_filter_info = body->getCollisionFilterInfo();

    if (body->isEntity()) {
        const u32 idx = group_handler ? group_handler->getIndex() : 0;
        collision_filter_info = [&] {
            EntityCollisionMask info{collision_filter_info};
            info.group_handler_index.SetUnsafe(idx);
            return info.raw;
        }();
    } else {
        const u32 idx = group_handler ? group_handler->getIndex() : 0;
        collision_filter_info = [&] {
            SensorCollisionMask info{collision_filter_info};
            info.group_handler_index.SetUnsafe(idx);
            return info.raw;
        }();
    }

    body->setCollisionFilterInfo(collision_filter_info);
    body->processUpdateRequests();
    return static_cast<RigidBodyT*>(body);
}

template <typename RigidBodyT, typename ShapeT, typename ParamT>
RigidBodyT* RigidBodyFromShape::cloneImpl(sead::Heap* heap,
                                          SystemGroupHandler* group_handler) const {
    ParamT derived_param;
    RigidBodyInstanceParam& param = derived_param;
    param.name = getHkBodyName().cstr();
    param.motion_type = getMotionType();
    param.mass = getMass();
    param.inertia = getInertiaLocal();
    param.center_of_mass = getCenterOfMassInLocal();
    param.linear_damping = getLinearDamping();
    param.angular_damping = getAngularDamping();
    param.gravity_factor = getGravityFactor();
    param.time_factor = getTimeFactor();
    param.max_linear_velocity = getMaxLinearVelocity();
    param.max_angular_velocity_rad = getMaxAngularVelocity();
    param.magne_mass_scaling_factor = getMagneMassScalingFactor();
    param.enable_deactivation = !hasFlag(RigidBody::Flag::_2000000);
    param.toi = hasFlag(RigidBody::Flag::HighQualityCollidable);
    param.system_group_handler = group_handler;
    param.contact_layer = getContactLayer();
    param.groundhit = getGroundHitType();
    param.contact_mask = mContactMask;

    if (isEntity()) {
        param.max_impulse = getMaxImpulse();
        param.col_impulse_scale = getColImpulseScale();
        param.water_buoyancy_scale = getWaterBuoyancyScale();
        param.water_flow_effective_rate = getWaterFlowEffectiveRate();
        param.water_flow_effective_rate = getWaterFlowEffectiveRate();
        param.friction_scale = getFrictionScale();
        param.restitution_scale = getRestitutionScale();
    }

    auto* shape = getShape_();
    return make<RigidBodyT, ShapeT>(*shape, &param, heap, group_handler);
}

template <typename RigidBodyT, typename ShapeT, typename ParamT>
RigidBodyT*
RigidBodyFromShape::createEntityShapeBodyImpl(const sead::SafeString& name, ContactLayer layer,
                                              RigidBodyFromShape* linked_body, sead::Heap* heap,
                                              SystemGroupHandler* group_handler) {
    auto* shape_base = std::as_const(*linked_body).getShape_();
    // XXX: get rid of the const_cast!
    auto* shape = sead::DynamicCast<ShapeT>(const_cast<Shape*>(shape_base));

    ParamT derived_param;
    RigidBodyInstanceParam& param = derived_param;
    param.name = name.cstr();
    param.motion_type = linked_body->getMotionType() == MotionType::Fixed ? MotionType::Fixed :
                                                                            MotionType::Keyframed;
    param.mass = linked_body->getMass();
    param.inertia = linked_body->getInertiaLocal();
    param.center_of_mass = linked_body->getCenterOfMassInLocal();
    param.linear_damping = linked_body->getLinearDamping();
    param.angular_damping = linked_body->getAngularDamping();
    param.gravity_factor = linked_body->getGravityFactor();
    param.time_factor = linked_body->getTimeFactor();
    param.max_linear_velocity = linked_body->getMaxLinearVelocity();
    param.max_angular_velocity_rad = linked_body->getMaxAngularVelocity();
    param.enable_deactivation = true;
    param.toi = linked_body->hasFlag(RigidBody::Flag::HighQualityCollidable);
    param.contact_layer = layer;
    param.groundhit = linked_body->getGroundHitType();
    param.system_group_handler = group_handler;

    RigidBody* body = make<RigidBodyT, ShapeT>(shape, false, param, heap);
    body->setLinkedRigidBody(linked_body);
    return static_cast<RigidBodyT*>(body);
}

}  // namespace ksys::phys
