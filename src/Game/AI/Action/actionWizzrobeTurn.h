#pragma once

#include "Game/AI/Action/actionHoverTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WizzrobeTurn : public HoverTurn {
    SEAD_RTTI_OVERRIDE(WizzrobeTurn, HoverTurn)
public:
    explicit WizzrobeTurn(const InitArg& arg);
    ~WizzrobeTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb0
    const bool* mIsWaitASFinish_s{};
    // static_param at offset 0xb8
    const bool* mSucEndWithASFinish_s{};
};

}  // namespace uking::action
