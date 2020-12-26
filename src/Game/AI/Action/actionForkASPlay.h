#pragma once

#include "Game/AI/Action/actionForkASPlayBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASPlay : public ForkASPlayBase {
    SEAD_RTTI_OVERRIDE(ForkASPlay, ForkASPlayBase)
public:
    explicit ForkASPlay(const InitArg& arg);
    ~ForkASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
