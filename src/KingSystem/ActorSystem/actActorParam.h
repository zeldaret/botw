#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcJob.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Thread/Event.h"
#include "KingSystem/Resource/resResourceActorLink.h"

namespace ksys {

namespace res {
class AIProgram;
class AISchedule;
class AnimationInfo;
class ASList;
class AttClientList;
class Awareness;
class BoneControl;
class Chemical;
class DamageParam;
class Drop;
class EventFlow;
class GParamList;
class LifeCondition;
class Lod;
class ModelList;
class Physics;
class RagdollBlendWeight;
class RagdollConfig;
class RagdollConfigList;
class Recipe;
class Shop;
class UMii;
}  // namespace res

namespace act {

// FIXME: incomplete
class ActorParam : public sead::hostio::Node {
public:
    enum class ResourceType {
        ActorLink = 0,
        ModelList = 1,
        ASList = 2,
        AIProgram = 3,
        GParamList = 4,
        Physics = 5,
        Chemical = 6,
        AttClientList = 7,
        AISchedule = 8,
        EventFlow = 9,
        DamageParam = 10,
        RagdollConfigList = 11,
        RagdollBlendWeight = 12,
        Awareness = 13,
        Unknown14 = 14,
        Unknown15 = 15,
        Unknown16 = 16,
        DropTable = 17,
        ShopData = 18,
        Recipe = 19,
        Lod = 20,
        BoneControl = 21,
        LifeCondition = 22,
        UMii = 23,
        AnimationInfo = 24,
    };

    struct Resources {
        res::ActorLink* mActorLink;
        res::ModelList* mModelList;
        res::ASList* mASList;
        res::AIProgram* mAIProgram;
        res::GParamList* mGParamList;
        res::Physics* mPhysics;
        res::Chemical* mChemical;
        res::AttClientList* mAttClientList;
        res::AISchedule* mAISchedule;
        res::EventFlow* mEventFlow;
        res::DamageParam* mDamageParam;
        res::RagdollConfigList* mRagdollConfigList;
        res::RagdollBlendWeight* mRagdollBlendWeight;
        res::Awareness* mAwareness;
        void* mResource14;
        void* mResource15;
        void* mResource16;
        res::Drop* mDropTable;
        res::Shop* mShopData;
        res::Recipe* mRecipe;
        res::Lod* mLod;
        res::BoneControl* mBoneControl;
        res::LifeCondition* mLifeCondition;
        res::UMii* mUMii;
        res::AnimationInfo* mAnimationInfo;
    };
    KSYS_CHECK_SIZE_NX150(Resources, 0xc8);

    ActorParam();
    virtual ~ActorParam();

    bool isDummyParam(res::ActorLink::Users::User user) const;

    u16 _8 = 0;
    u8 _a = 0;
    sead::FixedSafeString<64> mActorName;
    sead::SafeString mProfile;
    const char* mClassName{};
    Priority mPriority = Priority::AllAfter;
    u32 _74 = 2;
    Resources mRes;
    sead::Buffer<res::Handle> mHandles1;
    sead::Buffer<res::Handle> mHandles2;
    s32 mNumHandles1;
    s32 mNumHandles2;
    u32 _168{};

    static void resetDummyResources();

    static Resources sDummyResources;

private:
    friend class ActorParamMgr;

    void deleteData();
    void deleteResHandles();

    sead::CriticalSection mCS{nullptr};
    util::Event mEvent{nullptr,
                       sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified, true};
};
KSYS_CHECK_SIZE_NX150(ActorParam, 0x200);

}  // namespace act

}  // namespace ksys
