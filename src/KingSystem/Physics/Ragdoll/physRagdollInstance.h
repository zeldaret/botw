#pragma once

#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

class hkaRagdollInstance;
class hkQsTransformf;
class hkRootLevelContainer;

namespace gsys {
struct BoneAccessKey;
class Model;
}  // namespace gsys

namespace sead {
class DirectResource;
}

namespace ksys::phys {

class BoneAccessor;
class ModelBoneAccessor;
class RagdollParam;
class RagdollRigidBody;
class RigidBody;
class SkeletonMapper;
class SystemGroupHandler;
class UserTag;

enum class Fixed : bool;
enum class MarkLinearVelAsDirty : bool;
enum class PreserveVelocities : bool;

// TODO
class RagdollInstance : public sead::hostio::Node {
public:
    enum class SyncToThisBone : bool;

    struct Config {
        float _0;
        float _4;
        float _8;
        float _c;
        float _10;
        float _14;
        hkpConstraintInstance::ConstraintPriority priority = hkpConstraintInstance::PRIORITY_TOI;
    };

    explicit RagdollInstance(SystemGroupHandler* handler);
    virtual ~RagdollInstance();

    bool init(const RagdollParam* param, sead::DirectResource* res, gsys::Model* model,
              sead::Heap* heap);

    bool isAddedToWorld() const;
    void removeFromWorldImmediately();
    void removeFromWorld();
    bool removeFromWorldAndResetLinks();
    bool isAddingToWorld() const;

    void setTransform(const sead::Matrix34f& transform);
    void setScale(float scale);
    void setFixedAndPreserveImpulse(Fixed fixed, MarkLinearVelAsDirty mark_linear_vel_as_dirty);
    void resetFrozenState();
    void setUseSystemTimeFactor(bool use);
    void clearFlag400000(bool clear);
    void setEntityMotionFlag200(bool set);
    void setFixed(Fixed fixed, PreserveVelocities preserve_velocities);

    ModelBoneAccessor* getModelBoneAccessor() const;

    // TODO: rename
    virtual void m3();

    void setUserTag(UserTag* tag);
    void setSystemGroupHandler(SystemGroupHandler* handler);
    // 0x0000007101221424
    void x_22(int index, float value);
    void setContactPointInfo(ContactPointInfo* info);
    void enableContactLayer(ContactLayer layer);
    void disableContactLayer(ContactLayer layer);
    void setContactAll();
    void setContactNone();
    void setContactAll(int bone_index);
    void setContactNone(int bone_index);

    enum class WorldState {
        AddedToWorld = 0,
        NotAddedToWorld = 2,
    };
    void changeWorldState(WorldState state);
    WorldState getWorldState() const;

    void setExtraRigidBody(RigidBody* body, int bone_index);
    void setGravityFactor(float factor);

    RagdollRigidBody* getBoneRigidBodyByName(const sead::SafeString& name) const;
    int getBoneIndexByModelKey(const gsys::BoneAccessKey& key) const;
    int getBoneIndexByName(const sead::SafeString& name) const;
    int getParentOfBone(int index) const;

    RagdollRigidBody* getParentBoneRigidBody(const RigidBody* body) const;
    int getNumChildBones(const RigidBody* body) const;
    RagdollRigidBody* getChildBoneRigidBody(const RigidBody* body, int index) const;

    sead::Matrix34f getTransform(int bone_index) const;
    sead::Matrix34f getTransformWithCustomYAxis(int bone_index, const sead::Vector3f& y_axis) const;

    int getConstraintIndexByName(const sead::SafeString& name) const;
    int getNumConstraints() const;
    void enableConstraint(int index, bool enable);
    bool isConstraintEnabled(int index) const;

    void setContactLayer(ContactLayer layer);
    /// Sets whether a bone is keyframed.
    /// @param sync_to_this_bone Only used if keyframed = true.
    void setKeyframed(int bone_index, bool keyframed, SyncToThisBone sync_to_this_bone);
    void setUnk1(u8 value);
    static void setMaximumUnk1(u8 value);
    void stopForcingKeyframing();

    void update();

    static Config& getConfig();
    auto* getHavokRagdollInstance() const { return mRagdollInstance; }
    auto& getRigidBodies_() { return mBoneRigidBodies; }

private:
    class ScopedPhysicsLock {
    public:
        explicit ScopedPhysicsLock(const RagdollInstance* instance);
        ~ScopedPhysicsLock();

    private:
        const RagdollInstance* mInstance;
        ScopedWorldLock mWorldLock;
    };

    enum class Flag {
        _2 = 0x2,
        _4 = 0x4,
        _8 = 0x8,
        AddedToWorld = 0x10,
        _20 = 0x20,
        _40 = 0x40,
        _80 = 0x80,
        /// Whether this instance has been registered with the RagdollInstanceMgr.
        IsRegistered = 0x100,
        _200 = 0x200,
    };

    struct BoneVectors {
        sead::Vector3f _0 = sead::Vector3f::zero;
        sead::Vector3f _c = sead::Vector3f::zero;
        u16 _18 = -1;
        u16 _1a = -1;
    };

    bool doInit(const RagdollParam* param, sead::DirectResource* res, gsys::Model* model,
                sead::Heap* heap);
    void allocateBoneTransforms(int num_bones, sead::Heap* heap);
    void finalize();
    void removeConstraints();
    void setTransform(const hkQsTransformf& transform);

    void registerSelf();
    void unregisterSelf();

    void updateGravityFactorOverride();

    BoneAccessor* getBoneAccessor() const;

    SkeletonMapper* mSkeletonMapper = nullptr;
    ModelBoneAccessor* mModelBoneAccessor = nullptr;
    hkaRagdollInstance* mRagdollInstance = nullptr;
    SystemGroupHandler* mGroupHandler = nullptr;
    /// The rigid bodies of bones.
    sead::Buffer<RagdollRigidBody*> mBoneRigidBodies;
    // TODO: rename
    sead::Buffer<BoneVectors> mBoneVectors;
    // TODO: rename
    sead::Buffer<u32> mBoneStuff;
    hkRootLevelContainer* mRootLevelContainer = nullptr;
    sead::SafeString mName;
    u8* mRagdollData = nullptr;
    u32 mRagdollDataSize = 0;
    hkQsTransformf* mTransform = nullptr;
    // TODO: rename
    sead::Buffer<float> mBoneStuff2;
    float _98 = 0.1;
    float mGravityFactorOverride = 1.0;
    sead::Buffer<hkQsTransformf> mBoneTransforms;
    u32 mBoneTransformsByteSize = 0;
    const RagdollParam* mRagdollParam = nullptr;
    sead::TypedBitFlag<Flag> mFlags;
    sead::BitFlag32 mDisabledConstraints;
    sead::BitFlag32 mKeyframedBones;
    sead::BitFlag32 mKeyframedBonesToSyncTo;
    gsys::Model* mModel = nullptr;
    RigidBody* mExtraRigidBody = nullptr;
    void* _e0 = nullptr;
    u8 _e8;
    u8 _e9;
    u8 _ea = 0;
    u8 mBoneIndexForExtraRigidBody = 0;
    ContactLayer mContactLayer = ContactLayer::EntityRagdoll;
};
KSYS_CHECK_SIZE_NX150(RagdollInstance, 0xf0);

}  // namespace ksys::phys
