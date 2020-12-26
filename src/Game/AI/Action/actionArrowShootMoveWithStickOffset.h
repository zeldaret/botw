#pragma once

#include "Game/AI/Action/actionArrowShootMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ArrowShootMoveWithStickOffset : public ArrowShootMove {
    SEAD_RTTI_OVERRIDE(ArrowShootMoveWithStickOffset, ArrowShootMove)
public:
    explicit ArrowShootMoveWithStickOffset(const InitArg& arg);
    ~ArrowShootMoveWithStickOffset() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x150
    const float* mStickOffset_s{};
};

}  // namespace uking::action
