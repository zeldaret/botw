#pragma once

#include "Game/AI/Action/actionWindControl.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WindControlLength : public WindControl {
    SEAD_RTTI_OVERRIDE(WindControlLength, WindControl)
public:
    explicit WindControlLength(const InitArg& arg);
    ~WindControlLength() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x1a8
    const float* mWindLength_m{};
};

}  // namespace uking::action
