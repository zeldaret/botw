#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveKeyFramed : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MoveKeyFramed, ksys::act::ai::Action)
public:
    explicit MoveKeyFramed(const InitArg& arg);
    ~MoveKeyFramed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mAxisY_d{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mAxisZ_d{};
};

}  // namespace uking::action
