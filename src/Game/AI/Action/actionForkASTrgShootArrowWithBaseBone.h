#pragma once

#include "Game/AI/Action/actionForkASTrgShootArrow.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgShootArrowWithBaseBone : public ForkASTrgShootArrow {
    SEAD_RTTI_OVERRIDE(ForkASTrgShootArrowWithBaseBone, ForkASTrgShootArrow)
public:
    explicit ForkASTrgShootArrowWithBaseBone(const InitArg& arg);
    ~ForkASTrgShootArrowWithBaseBone() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const float* mFrontDirAngle_s{};
    // static_param at offset 0x80
    const bool* mIsAddTargetActorAimPosHeight_s{};
    // static_param at offset 0x88
    sead::SafeString mBaseBoneName_s{};
    // static_param at offset 0x98
    const sead::Vector3f* mFrontDirOfBaseBone_s{};
};

}  // namespace uking::action
