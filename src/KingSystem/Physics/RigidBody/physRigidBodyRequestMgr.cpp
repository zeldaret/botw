#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/System/physMaterialMask.h"

namespace ksys::phys {

RigidBodyRequestMgr::RigidBodyRequestMgr() = default;

RigidBodyRequestMgr::~RigidBodyRequestMgr() {
    for (int i = 0; i < NumRigidBodyBuffers; ++i) {
        mRigidBodies1[i].freeBuffer();
        mRigidBodies2[i].freeBuffer();
    }

    _38.freeBuffer();
    _50.freeBuffer();
    _98.freeBuffer();
    _b0.freeBuffer();
    _c8.freeBuffer();
    _e0.freeBuffer();
    _120.freeBuffer();
    _138.freeBuffer();
    _108.freeBuffer();
    _f8.freeBuffer();

    if (mContactPoints) {
        ksys::phys::RigidContactPointsEx::free(mContactPoints);
        mContactPoints = nullptr;
    }
}

void RigidBodyRequestMgr::init(sead::Heap* heap) {
    constexpr int Buffer138Size = 0x800;

    _108.allocBufferAssert(0x100, heap);
    _118 = 0;

    _120.allocBufferAssert(0x100, heap);
    _130 = 0;

    for (int i = 0; i < NumRigidBodyBuffers; ++i) {
        mRigidBodies1[i].alloc(0x2000, heap);
        mRigidBodies2[i].alloc(0x100, heap);
    }

    _38.alloc(0x800, heap);
    _50.alloc(0x800, heap);
    _98.alloc(0x100, heap);
    _b0.alloc(0x100, heap);
    _f8.allocBuffer(0x400, heap);
    _138.allocBufferAssert(Buffer138Size, heap);
    _c8.alloc(0x800, heap);
    _e0.alloc(Buffer138Size, heap);

    for (int i = 0; i < Buffer138Size; ++i) {
        _e0.push(&_138[i]);
    }

    _148 = 0;

    mContactPoints =
        RigidContactPointsEx::make(heap, 0x1000, 11, "RigidBodyRequestMgr::Water", 0, 0, 0);

    mContactPoints->setCallback(&mCallback);
    mContactPoints->set30(1);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityObject);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntitySmallObject);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityGroundObject);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityTree);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityRope);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityRagdoll);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityNPC);
    mContactPoints->registerLayerPair(ContactLayer::EntityWater, ContactLayer::EntityPlayer);
    mContactPoints->registerLayerPair(ContactLayer::EntityGround, ContactLayer::EntityPlayer);
    mContactPoints->registerLayerPair(ContactLayer::EntityGround, ContactLayer::EntityObject);
    mContactPoints->registerLayerPair(ContactLayer::EntityGround, ContactLayer::EntitySmallObject);

    mWaterIceSubmatIdx = MaterialMask::getSubMaterialIdx(Material::Water, "Water_Ice");
    mWaterHotSubmatIdx = MaterialMask::getSubMaterialIdx(Material::Water, "Water_Hot");
    mWaterPoisonSubmatIdx = MaterialMask::getSubMaterialIdx(Material::Water, "Water_Poison");
}

}  // namespace ksys::phys
