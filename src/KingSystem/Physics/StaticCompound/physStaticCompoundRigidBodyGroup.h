#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

class hkpPhysicsSystem;
class hkpShape;

namespace ksys::phys {

enum class BodyLayerType;
class RigidBody;
class StaticCompound;

class StaticCompoundRigidBodyGroup {
public:
    StaticCompoundRigidBodyGroup();
    ~StaticCompoundRigidBodyGroup();

    StaticCompoundRigidBodyGroup(const StaticCompoundRigidBodyGroup&) = delete;
    auto operator=(const StaticCompoundRigidBodyGroup&) = delete;

    void init(const hkpPhysicsSystem& system, sead::Matrix34f* mtx, StaticCompound* sc,
              sead::Heap* heap);

    void disableCollision(BodyLayerType body_layer_type, int instance_id, bool x);

    void modifyMatrix(const sead::Matrix34f& matrix, int index);

private:
    enum class Flag {
        Initialised = 1 << 0,
        HasModifiedMatrix = 1 << 3,
    };

    struct Unk1 {
        virtual ~Unk1();

        u8 _8[0xc0];
    };

    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags;
    sead::Atomic<u32> mModifiedMatrices;
    sead::Buffer<RigidBody*> mRigidBodiesPerBodyLayerType;
    sead::Buffer<const hkpShape*> mShapesPerBodyLayerType;
    // TODO: rename
    sead::Buffer<sead::Matrix34f> mMatrices;
    sead::Buffer<sead::Matrix34f> mMatrices2;
    sead::Matrix34f mMtx0 = sead::Matrix34f::ident;
    sead::Matrix34f mMtx1 = sead::Matrix34f::ident;
    sead::Matrix34f* mMtxPtr{};
    sead::PtrArray<RigidBody> mRigidBodies;
    StaticCompound* mStaticCompound{};
    sead::Vector3f _c8 = sead::Vector3f::zero;
    sead::Vector3f _d4 = sead::Vector3f::zero;
    u32 _e0{};
    sead::Buffer<Unk1> _e8;
};
KSYS_CHECK_SIZE_NX150(StaticCompoundRigidBodyGroup, 0xf8);

}  // namespace ksys::phys
