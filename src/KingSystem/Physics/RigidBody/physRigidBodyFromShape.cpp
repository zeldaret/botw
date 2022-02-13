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
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Physics/physConversions.h"
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

}  // namespace ksys::phys
