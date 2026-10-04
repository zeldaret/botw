#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkBombIgniteCarriedByPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkBombIgniteCarriedByPlayer, ksys::act::ai::Action)
public:
    explicit ForkBombIgniteCarriedByPlayer(const InitArg& arg);
    ~ForkBombIgniteCarriedByPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mASName_s{};
    // aitree_variable at offset 0x30
    bool* mIsIgniteCarriedBomb_a{};
};

}  // namespace uking::action
