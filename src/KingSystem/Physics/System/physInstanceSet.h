#pragma once

#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadObjArray.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace gsys {
class Model;
}

namespace sead {
class DirectResource;
}

namespace ksys::res {
class Handle;
class RagdollBlendWeight;
class RagdollConfigList;
}  // namespace ksys::res

namespace ksys::phys {

class CharacterController;
class CharacterFormSet;
class ClothSet;
class CollisionInfo;
class ContactPointInfo;
class NavMeshCharacter;
class ParamSet;
class RagdollController;
class RigidBodySet;
class SystemGroupHandler;
class UserTag;

// TODO: move to a separate header
class CharacterController {
public:
    void sub_7100F5EC30();
    void sub_7100F60604();
    void enableCollisionMaybe_0(ContactLayer);
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

    InstanceSet(const sead::SafeString& actor_name, const sead::SafeString& actor_profile,
                const ParamSet& param_set);
    virtual ~InstanceSet();

    const sead::SafeString& getName() const { return mName; }
    const ParamSet* getParamSet() const { return mParamSet; }

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
    struct Unk1 {
        u8 _0[0x48];
    };

    sead::SafeString mName;
    const ParamSet* mParamSet;
    sead::TypedBitFlag<Flag> mFlags;
    u16 _24{};
    u16 _26{};
    gsys::Model* mModel;
    f32 mScale;
    UserTag* mUserTag;
    sead::PtrArray<RigidBodySet> mRigidBodySets;
    sead::PtrArray<CollisionInfo> mCollisionInfo;
    sead::PtrArray<ContactPointInfo> mContactPointInfo;
    sead::Buffer<res::Handle*> mRigidBodySetResHandles;

    CharacterController* mCharacterController{};
    CharacterFormSet* mCharacterFormSet{};

    RagdollController* mRagdollController{};
    sead::Buffer<void*> _98;
    ContactPointInfo* mRagdollContactPointInfo{};
    res::Handle* mRagdollResHandle{};
    res::RagdollBlendWeight* mRagdollBlendWt;
    res::RagdollConfigList* mRagdollConfigList;

    res::Handle* mClothResHandle{};
    sead::DirectResource* mClothRes{};
    ClothSet* mClothSet;

    res::Handle* mSupportBoneResHandle{};
    void* _e8{};
    void* _f0{};

    NavMeshCharacter* mNavMeshCharacter;
    sead::Buffer<void*> _100;
    u16 _110{};
    sead::ObjArray<Unk1> mLinkMatricesMaybe;
    sead::Buffer<void*> _138;
    sead::TList<RigidBody*> mList;
    sead::ListNode _160;
    u32 _170{};
    SystemGroupHandler* _178[2];
    SystemGroupHandler* _188[2];
};
KSYS_CHECK_SIZE_NX150(InstanceSet, 0x198);

}  // namespace ksys::phys
