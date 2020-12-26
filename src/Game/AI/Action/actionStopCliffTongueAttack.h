#pragma once

#include "Game/AI/Action/actionOnCliffWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StopCliffTongueAttack : public OnCliffWait {
    SEAD_RTTI_OVERRIDE(StopCliffTongueAttack, OnCliffWait)
public:
    explicit StopCliffTongueAttack(const InitArg& arg);
    ~StopCliffTongueAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    sead::SafeString mRigidName_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
