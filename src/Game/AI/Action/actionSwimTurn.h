#pragma once

#include "Game/AI/Action/actionSwimTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimTurn : public SwimTurnBase {
    SEAD_RTTI_OVERRIDE(SwimTurn, SwimTurnBase)
public:
    explicit SwimTurn(const InitArg& arg);
    ~SwimTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe8
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
