#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAnimDriveMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAnimDriveMove, ksys::act::ai::Action)
public:
    explicit ForkAnimDriveMove(const InitArg& arg);
    ~ForkAnimDriveMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mTargetBone_s{};
};

}  // namespace uking::action
