#include "KingSystem/Physics/StaticCompound/physStaticCompoundRigidBodyGroup.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/World/hkpPhysicsSystem.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyFromResource.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundInfo.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

// TODO: rename
constexpr int BodyGroupNumMatrices = 8;

StaticCompoundRigidBodyGroup::StaticCompoundRigidBodyGroup() = default;

StaticCompoundRigidBodyGroup::~StaticCompoundRigidBodyGroup() {
    mFlags.reset(Flag::Initialised);

    for (int i = 0, n = mRigidBodiesPerBodyLayerType.size(); i < n; ++i) {
        delete mRigidBodiesPerBodyLayerType[i];
    }

    mRigidBodiesPerBodyLayerType.freeBuffer();
    mShapesPerBodyLayerType.freeBuffer();
    mMatrices2.freeBuffer();
    mMatrices.freeBuffer();
    _e8.freeBuffer();
    mRigidBodies.freeBuffer();
}

void StaticCompoundRigidBodyGroup::init(const hkpPhysicsSystem& system, sead::Matrix34f* mtx, StaticCompound* sc,
                     sead::Heap* heap) {
    mStaticCompound = sc;
    mMtxPtr = mtx;

    const int num_rigid_bodies = system.getRigidBodies().getSize();

    mRigidBodies.allocBuffer(num_rigid_bodies + NumBodyLayerTypes, heap);

    if (num_rigid_bodies > 0) {
        auto* group_handler = System::instance()->getStaticCompoundMgr()->getGroupHandler();

        mRigidBodiesPerBodyLayerType.allocBufferAssert(NumBodyLayerTypes, heap);
        mShapesPerBodyLayerType.allocBufferAssert(NumBodyLayerTypes, heap);
        for (int i = 0; i < NumBodyLayerTypes; ++i) {
            mRigidBodiesPerBodyLayerType[i] = nullptr;
            mShapesPerBodyLayerType[i] = nullptr;
        }

        for (int i = 0; i < num_rigid_bodies; ++i) {
            hkpRigidBody* hk_body = system.getRigidBodies()[i];

            bool is_entity = sead::SafeString(hk_body->getName()).include("Entity");
            auto layer_type = is_entity ? ContactLayerType::Entity : ContactLayerType::Sensor;

            auto* body = new (heap) RigidBodyFromResource(0.0, hk_body, layer_type, heap,
                                                          RigidBody::Type::StaticCompoundBody);

            RigidBodyInstanceParam param;
            param.max_linear_velocity = 1000;
            body->initMotionAccessor(param, heap, /* init_motion */ false);

            BodyLayerType body_layer_type = getBodyLayerType(body->getContactLayer());
            mRigidBodiesPerBodyLayerType[int(body_layer_type)] = body;

            body->updateCollidableQualityType(true);
            body->changeMotionType(MotionType::Fixed);
            if (body->isEntity()) {
                body->setSystemGroupHandler(group_handler);
                body->enableGroundCollision(false);
                body->enableWaterCollision(false);
            }

            mRigidBodies.pushBack(body);

            // XXX: eww, const_cast
            auto* shape =
                const_cast<hkpShape*>(system.getRigidBodies()[i]->getCollidable()->getShape());
            shape->m_userData = reinterpret_cast<hkUlong>(this);
            mShapesPerBodyLayerType[int(body_layer_type)] = shape;
        }
    }

    mMatrices2.allocBufferAssert(BodyGroupNumMatrices, heap);
    mMatrices.allocBufferAssert(BodyGroupNumMatrices, heap);
    for (int i = 0, n = mMatrices2.size(); i < n; ++i) {
        mMatrices2[i].makeIdentity();
        mMatrices[i].makeIdentity();
    }

    mFlags.set(Flag::Initialised);
}

void StaticCompoundRigidBodyGroup::modifyMatrix(const sead::Matrix34f& matrix, int index) {
    if (mMatrices[index] == matrix)
        return;

    mMatrices[index] = matrix;
    mModifiedMatrices |= 1 << index;
    mFlags.set(Flag::HasModifiedMatrix);
}

}  // namespace ksys::phys
