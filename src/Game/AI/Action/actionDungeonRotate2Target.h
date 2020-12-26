#pragma once

#include "Game/AI/Action/actionDungeonRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonRotate2Target : public DungeonRotateBase {
    SEAD_RTTI_OVERRIDE(DungeonRotate2Target, DungeonRotateBase)
public:
    explicit DungeonRotate2Target(const InitArg& arg);
    ~DungeonRotate2Target() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc8
    const int* mDgnRotDir_s{};
    // static_param at offset 0xd0
    const float* mRotSpAccel_s{};
    // static_param at offset 0xd8
    const float* mRotSpSlowDown_s{};
    // static_param at offset 0xe0
    const float* mRotSpSlowDownTh_s{};
    // static_param at offset 0xe8
    const float* mMinRotSp_s{};
    // static_param at offset 0xf0
    const float* mRotReverseSlowDown_s{};
    // aitree_variable at offset 0xf8
    float* mTargetRad_a{};
    // aitree_variable at offset 0x100
    float* mTargetRadMax_a{};
    // aitree_variable at offset 0x108
    float* mTargetRadMin_a{};
};

}  // namespace uking::action
