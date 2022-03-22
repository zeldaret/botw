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
class hkpStaticCompoundShape;

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

    /// @returns whether any rigid body in this group has been added to the world.
    bool isAnyRigidBodyAddedToWorld() const;

    /// @returns whether any rigid body in this group is being added to the world.
    bool isAnyRigidBodyBeingAddedToWorld() const;

    void addToWorld();
    void removeFromWorld();
    /// Force the removal of all rigid bodies in the group. This is unlike removeFromWorld,
    /// which merely requests the removal asynchronously.
    void removeFromWorldImmediately();

    bool setInstanceEnabled(BodyLayerType body_layer_type, int instance_id, bool enabled);
    void enableAllInstancesAndShapeKeys();

    void modifyMatrix(const sead::Matrix34f& matrix, int index);

private:
    enum class Flag {
        Initialised = 1 << 0,
        _2 = 1 << 1,
        _4 = 1 << 2,
        HasModifiedMatrix = 1 << 3,
        _10 = 1 << 4,
        HasEnabledOrDisabledInstance = 1 << 5,
    };

    struct Unk1 {
        virtual ~Unk1();

        u8 _8[0xc0];
    };

    const sead::Matrix34f& getMatrix();

    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags;
    sead::Atomic<u32> mModifiedMatrices;
    sead::Buffer<RigidBody*> mRigidBodiesPerBodyLayerType;
    sead::Buffer<hkpStaticCompoundShape*> mShapesPerBodyLayerType;
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
