#pragma once

#include "Game/AI/Action/actionSlippedCircleWalkBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SlippedCircleWalk : public SlippedCircleWalkBase {
    SEAD_RTTI_OVERRIDE(SlippedCircleWalk, SlippedCircleWalkBase)
public:
    explicit SlippedCircleWalk(const InitArg& arg);
    ~SlippedCircleWalk() override;

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
