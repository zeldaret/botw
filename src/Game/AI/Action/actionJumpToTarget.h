#pragma once

#include "Game/AI/Action/actionJumpTo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class JumpToTarget : public JumpTo {
    SEAD_RTTI_OVERRIDE(JumpToTarget, JumpTo)
public:
    explicit JumpToTarget(const InitArg& arg);
    ~JumpToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa0
    sead::SafeString mPreJumpAS_s{};
    // static_param at offset 0xb0
    sead::SafeString mJumpAS_s{};
    // static_param at offset 0xc0
    sead::SafeString mLandAS_s{};
};

}  // namespace uking::action
