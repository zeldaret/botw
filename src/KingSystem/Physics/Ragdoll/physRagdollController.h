#pragma once

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
class hkRotationf;

namespace gsys {
class Model;
}

namespace sead {
class DirectResource;
}

namespace ksys::phys {

class BoneAccessor;
class ModelBoneAccessor;
class RagdollParam;
class RigidBody;
class SkeletonMapper;
class SystemGroupHandler;

// TODO
class RagdollController : public sead::hostio::Node {
public:
    explicit RagdollController(SystemGroupHandler* handler);
    virtual ~RagdollController();

    // 0x000000710121e5dc
    void init(const RagdollParam* param, sead::DirectResource* res, gsys::Model* model,
              sead::Heap* heap);

    // 0x0000007101223320
    void update();

    bool isAddedToWorld() const;
    void removeFromWorldImmediately();
    void removeFromWorld();
    bool removeFromWorldAndResetLinks();
    bool isAddingToWorld() const;

    void setTransform(const sead::Matrix34f& transform);
    void setScale(float scale);

    u32 sub_7101221CC4();
    void sub_7101221728(ContactLayer layer);
    void sub_71012217A8();

    // TODO: rename
    virtual void m3();

    static void setUnk1(u8 value);

private:
    class ScopedPhysicsLock {
    public:
        explicit ScopedPhysicsLock(const RagdollController* ctrl);
        ~ScopedPhysicsLock();

    private:
        const RagdollController* mCtrl;
        ScopedWorldLock mWorldLock;
    };

    enum class Flag {
        /// Whether this controller has been registered with the RagdollControllerMgr.
        IsRegistered = 0x100,
    };

    struct BoneVectors {
        sead::Vector3f _0;
        sead::Vector3f _c;
        float _18;
    };

    void finalize();
    void removeConstraints();
    void setTransform(const hkQsTransformf& transform);

    BoneAccessor* getBoneAccessor() const;

    SkeletonMapper* mSkeletonMapper = nullptr;
    ModelBoneAccessor* mModelBoneAccessor = nullptr;
    hkaRagdollInstance* mRagdollInstance = nullptr;
    SystemGroupHandler* mGroupHandler = nullptr;
    sead::Buffer<RigidBody*> mRigidBodies;
    // TODO: rename
    sead::Buffer<BoneVectors> mBoneVectors;
    // TODO: rename
    sead::Buffer<u32> mBoneStuff;
    hkRootLevelContainer* mRootLevelContainer = nullptr;
    sead::SafeString mName;
    u8* mRawRagdollData = nullptr;
    int mRawRagdollDataSize = 0;
    hkRotationf* mRotations = nullptr;
    // TODO: type
    sead::Buffer<void*> mBones;
    float _98 = 0.1;
    float _9c = 1.0;
    u32 _a0 = 0;
    // TODO: type
    u8* _a8 = nullptr;
    u32 _b0 = 0;
    const RagdollParam* mRagdollParam = nullptr;
    sead::TypedBitFlag<Flag> mFlags;
    u32 _c4 = 0;
    u32 _c8 = 0;
    u32 _cc = 0;
    gsys::Model* mModel = nullptr;
    RigidBody* mExtraRigidBody = nullptr;
    void* _e0 = nullptr;
    u8 _e8;
    u8 _e9;
    u8 _ea = 0;
    u8 mRigidBodyIndex = 0;
    u32 _ec = 5;
};
KSYS_CHECK_SIZE_NX150(RagdollController, 0xf0);

}  // namespace ksys::phys
