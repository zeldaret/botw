#pragma once

#include "Game/AI/Action/actionSlippedBackWalkBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SlippedBackWalk : public SlippedBackWalkBase {
    SEAD_RTTI_OVERRIDE(SlippedBackWalk, SlippedBackWalkBase)
public:
    explicit SlippedBackWalk(const InitArg& arg);
    ~SlippedBackWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb8
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
