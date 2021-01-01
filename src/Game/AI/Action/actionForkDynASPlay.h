#pragma once

#include "Game/AI/Action/actionForkASPlayBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkDynASPlay : public ForkASPlayBase {
    SEAD_RTTI_OVERRIDE(ForkDynASPlay, ForkASPlayBase)
public:
    explicit ForkDynASPlay(const InitArg& arg);
    ~ForkDynASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x50
    sead::SafeString mDynASKey_d{};
};

}  // namespace uking::action
