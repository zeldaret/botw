#pragma once

#include "Game/AI/AI/aiOctarockRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockRoot : public OctarockRootBase {
    SEAD_RTTI_OVERRIDE(OctarockRoot, OctarockRootBase)
public:
    explicit OctarockRoot(const InitArg& arg);
    ~OctarockRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    const bool* mIsWigBreakable_s{};
    // static_param at offset 0x1e0
    sead::SafeString mItemName_s{};
    // static_param at offset 0x1f0
    sead::SafeString mConnectRigidBodyName_s{};
    // static_param at offset 0x200
    sead::SafeString mConnectTgtBodyName_s{};
    // static_param at offset 0x210
    sead::SafeString mShootActorName_s{};
    // static_param at offset 0x250
    sead::SafeString mExtraShootActorName_s{};
    // static_param at offset 0x260
    sead::SafeString mExtraShootActorKey_s{};
    // map_unit_param at offset 0x270
    sead::SafeString mCarryActorName_m{};
    // aitree_variable at offset 0x280
    void* mVacuumedExplodingBomb_a{};
    // aitree_variable at offset 0x288
    void* mOctarockFormChangeUnit_a{};
};

}  // namespace uking::ai
