#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StalEnemyHeadShotReaction : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(StalEnemyHeadShotReaction, ActionWithPosAngReduce)
public:
    explicit StalEnemyHeadShotReaction(const InitArg& arg);
    ~StalEnemyHeadShotReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const float* mSpeed_s{};
    // static_param at offset 0x38
    const float* mRotSpd_s{};
    // static_param at offset 0x40
    const bool* mUseAddVec_s{};
    // static_param at offset 0x48
    const bool* mIsTgOff_s{};
    // static_param at offset 0x50
    const bool* mIsDropWeapon_s{};
    // static_param at offset 0x58
    const bool* mIsChangeable_s{};
    // static_param at offset 0x60
    sead::SafeString mASName_s{};
    // static_param at offset 0x70
    sead::SafeString mHeadBoneKey_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mAddVec_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mRotVec_s{};
};

}  // namespace uking::action
