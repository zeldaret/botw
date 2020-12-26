#pragma once

#include "Game/AI/Action/actionSlippedWalkBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SlippedWalk : public SlippedWalkBase {
    SEAD_RTTI_OVERRIDE(SlippedWalk, SlippedWalkBase)
public:
    explicit SlippedWalk(const InitArg& arg);
    ~SlippedWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
