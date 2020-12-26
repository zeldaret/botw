#pragma once

#include "Game/AI/Action/actionTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HoverTurn : public TurnBase {
    SEAD_RTTI_OVERRIDE(HoverTurn, TurnBase)
public:
    explicit HoverTurn(const InitArg& arg);
    ~HoverTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0x98
    sead::SafeString mASKeyName_s{};
};

}  // namespace uking::action
