#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetComebackPosition : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(SetComebackPosition, AreaTagAction)
public:
    explicit SetComebackPosition(const InitArg& arg);
    ~SetComebackPosition() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x38
    const float* mAngleY_m{};
};

}  // namespace uking::action
