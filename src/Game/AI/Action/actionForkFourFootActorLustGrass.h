#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkFourFootActorLustGrass : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkFourFootActorLustGrass, ksys::act::ai::Action)
public:
    explicit ForkFourFootActorLustGrass(const InitArg& arg);
    ~ForkFourFootActorLustGrass() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    void* mGanonBeastGrudgeMarkMgr_a{};
    // static_param at offset 0x28
    const float* mMaxRadius_s{};
    // static_param at offset 0x30
    const float* mMinRadius_s{};
    // static_param at offset 0x38
    const float* mRadSpd_s{};
    // static_param at offset 0x40
    sead::SafeString mNode1Name_s{};
    // static_param at offset 0x50
    sead::SafeString mNode2Name_s{};
    // static_param at offset 0x60
    sead::SafeString mNode3Name_s{};
    // static_param at offset 0x70
    sead::SafeString mNode4Name_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mWorldOffset_s{};
};

}  // namespace uking::action
