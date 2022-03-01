#pragma once

#include <container/seadListImpl.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace gsys {
class Model;
}

namespace ksys::res {
class RagdollBlendWeight;
class RagdollConfigList;
}  // namespace ksys::res

namespace ksys::phys {

class ParamSet;
class RigidBodySet;
class SystemGroupHandler;

class Ragdoll {};

class RagdollController {
public:
    u32 sub_7101221CC4();
    void sub_7101221728(ContactLayer);
    void sub_71012217A8();
};

class CollisionController {
public:
    void sub_7100F5EC30();
    void sub_7100F60604();
    void enableCollisionMaybe_0(ContactLayer);
};

struct CollisionInfoBase {
    u8 filler[0x50];
    sead::SafeString mName;
};

struct ContactInfo {
    u8 filler[0x8];
    sead::SafeString mName;
};

class InstanceSet : public sead::hostio::Node {
public:
    enum class Flag : u32 {
        _1 = 1 << 0,
        _2 = 1 << 1,
        _8 = 1 << 3,
        DisableDraw = 1 << 2,
        _200000 = 1 << 21,
        Cloth1 = 1 << 22,
        Cloth2 = 1 << 23,
        Cloth3 = 1 << 24,
        InDemo = 1 << 25,
        _80000000 = 1u << 31,
    };

    const sead::SafeString& getName() const { return mName; }
    ParamSet* getParamSet() const { return mParamSet; }

    void setFlag2();
    void clothVisibleStuff();
    void setInDemo();
    void resetInDemo();
    void clothVisibleStuff_0(s32 setting);
    void sub_7100FB9BAC(InstanceSet* other);
    u32 sub_7100FB9C2C() const;
    void sub_7100FBA9BC();
    void sub_7100FBACE0(ContactLayer layer);
    void sub_7100FBAD74();
    void* sub_7100FBAEDC(s32 rigidbody_idx, s32 ragdoll_idx) const;
    void sub_7100FBB00C(RigidBody* body, RigidBodyParam* param);
    void setMtxAndScale(const sead::Matrix34f& mtx, bool a2, bool a3, f32 scale);
    void sub_7100FBB4B4();
    void* findX(const sead::SafeString& a1, const sead::SafeString& a2) const;
    void* sub_7100FBBC28(const sead::SafeString& name) const;
    s32 sub_7100FBBC78(const sead::SafeString& name) const;
    s32 sub_7100FBBD9C(const sead::SafeString& name) const;
    void sub_7100FBD284(const sead::Matrix34f& mtx);
    void sub_7100FBC890(const sead::Matrix34f& mtx, bool a2, bool a3);
    s32 sub_7100FBDA2C(const sead::SafeString& name) const;

private:
    sead::SafeString mName;
    ParamSet* mParamSet;
    sead::TypedBitFlag<Flag> mFlags;
    gsys::Model* mModel;
    f32 mScale;
    u8 _34[0x40 - 0x34];
    sead::PtrArray<RigidBodySet> mRigidBodySets;
    sead::PtrArray<CollisionInfoBase> mCollisionInfos;
    sead::PtrArray<ContactInfo> mContactInfos;

    u8 _70[0x10];
    CollisionController* mCollisionController;
    u8 _88[8];
    RagdollController* mRagdollController;
    u8 _98[0xb8 - 0x98];
    res::RagdollBlendWeight* mRagdollBlendWt;
    res::RagdollConfigList* mRagdollConfigList;
    u8 _c8[0xd8 - 0xc8];
    void* _d8;
    u8 _e0[0x148 - 0xe0];
    sead::TList<RigidBody*> mList;
    u8 _160[0x178 - 0x160];
    SystemGroupHandler* _178[2];
    SystemGroupHandler* _188[2];
};
KSYS_CHECK_SIZE_NX150(InstanceSet, 0x198);

}  // namespace ksys::phys
