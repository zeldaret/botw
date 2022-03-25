#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

class hkReferencedObject;
class hkpPhysicsSystem;
class hkpStaticCompoundShape;

namespace ksys::phys {

enum class BodyLayerType;
class RigidBody;
class StaticCompound;

class StaticCompoundRigidBodyGroup {
public:
    struct Config {
        float unk1 = 1;
        int move_duration_ticks = 30;
        float unk2 = 1;
        float unk3 = 1;
    };

    struct Epsilons {
        float linvel = 0;
        float angvel = 0;
    };

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

    void resetExtraTransforms();
    void resetExtraTransformsAndApply();
    void applyExtraTransforms();
    void recomputeTransformMatrix();

    void setExtraTransform(const sead::Matrix34f& matrix, int index);
    const sead::Matrix34f& getExtraTransform(int index) const;

    sead::Matrix34f getTransformedMatrix(const sead::Matrix34f& mtx) const;
    sead::Matrix34f getInvTransformedMatrix(const sead::Matrix34f& mtx) const;
    sead::Vector3f getTransformedPos(const sead::Vector3f& pos) const;
    sead::Vector3f getRotatedDir(const sead::Vector3f& dir) const;

    RigidBody* getRigidBody(BodyLayerType body_layer_type) const;
    StaticCompound* getStaticCompound() const { return mStaticCompound; }

    void processUpdates();

    static Config& getConfig();
    static Epsilons& getEpsilons();

private:
    enum class Flag {
        Initialised = 1 << 0,
        ShouldRecomputeExtraTransform = 1 << 1,
        ShouldRecomputeTransform = 1 << 2,
        ShouldMoveBody = 1 << 3,
        IsMovingBody = 1 << 4,
        HasEnabledOrDisabledInstance = 1 << 5,
    };

    // A type with a virtual destructor. Nothing else is known about it.
    struct Unk2 {
        virtual ~Unk2() = default;
    };

    // The remnants of a type that had a virtual destructor and a bunch of pointers.
    // Nothing else is known about it.
    struct Unk1 {
        virtual ~Unk1();

        Unk2* _8;
        hkReferencedObject* _10;
        hkReferencedObject* _18;
        hkReferencedObject* _20;
        u8 _28[0xc8 - 0x28];
    };

    const sead::Matrix34f& getTransform() const;

    float getVelocityMultiplier() const;

    mutable sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags;
    sead::Atomic<u32> mPendingTransformChanges;
    sead::Buffer<RigidBody*> mRigidBodiesPerBodyLayerType;
    sead::Buffer<hkpStaticCompoundShape*> mShapesPerBodyLayerType;
    sead::Buffer<sead::Matrix34f> mPendingExtraTransforms;
    sead::Buffer<sead::Matrix34f> mExtraTransforms;
    mutable sead::Matrix34f mCombinedExtraTransform = sead::Matrix34f::ident;
    mutable sead::Matrix34f mTransform = sead::Matrix34f::ident;
    sead::Matrix34f* mMtxPtr{};
    sead::PtrArray<RigidBody> mRigidBodies;
    StaticCompound* mStaticCompound{};
    sead::Vector3f mLinearVelocity = sead::Vector3f::zero;
    sead::Vector3f mAngularVelocity = sead::Vector3f::zero;
    int mUpdateTimer{};
    sead::Buffer<Unk1> _e8;
};
KSYS_CHECK_SIZE_NX150(StaticCompoundRigidBodyGroup, 0xf8);

}  // namespace ksys::phys
