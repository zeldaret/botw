#pragma once

#include "Game/AI/Action/actionTargetCircle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TargetCircleMoveKeepDist : public TargetCircle {
    SEAD_RTTI_OVERRIDE(TargetCircleMoveKeepDist, TargetCircle)
public:
    explicit TargetCircleMoveKeepDist(const InitArg& arg);
    ~TargetCircleMoveKeepDist() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
