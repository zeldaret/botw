#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCLerpAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCLerpAction, ksys::act::ai::Action)
public:
    explicit NPCLerpAction(const InitArg& arg);
    ~NPCLerpAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotateSpeed_s{};
    // static_param at offset 0x28
    const float* mArriveDist_s{};
    // static_param at offset 0x30
    const bool* mIsRotateByRot_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetRot_d{};
};

}  // namespace uking::action
