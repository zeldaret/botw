#pragma once

#include "Game/AI/Action/actionBackWalkBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SlippedBackWalkBase : public BackWalkBase {
    SEAD_RTTI_OVERRIDE(SlippedBackWalkBase, BackWalkBase)
public:
    explicit SlippedBackWalkBase(const InitArg& arg);
    ~SlippedBackWalkBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb0
    const float* mAccRatio_s{};
};

}  // namespace uking::action
