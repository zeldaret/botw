#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkStalEnemyHeadShot : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkStalEnemyHeadShot, ksys::act::ai::Action)
public:
    explicit ForkStalEnemyHeadShot(const InitArg& arg);
    ~ForkStalEnemyHeadShot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mVisibleCount_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mRotSpd_s{};
    // static_param at offset 0x38
    const bool* mUseAddVec_s{};
    // static_param at offset 0x40
    sead::SafeString mHeadBoneKey_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mAddVec_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mRotVec_s{};
};

}  // namespace uking::action
