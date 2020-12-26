#pragma once

#include "Game/AI/Action/actionForkASPlayBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonBeastDamageASPlay : public ForkASPlayBase {
    SEAD_RTTI_OVERRIDE(GanonBeastDamageASPlay, ForkASPlayBase)
public:
    explicit GanonBeastDamageASPlay(const InitArg& arg);
    ~GanonBeastDamageASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const bool* mIsStateChange_s{};
    // aitree_variable at offset 0x58
    int* mLastDamageWeakPointIdx_a{};
};

}  // namespace uking::action
