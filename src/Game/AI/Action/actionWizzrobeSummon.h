#pragma once

#include "Game/AI/Action/actionTurnIgnite.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WizzrobeSummon : public TurnIgnite {
    SEAD_RTTI_OVERRIDE(WizzrobeSummon, TurnIgnite)
public:
    explicit WizzrobeSummon(const InitArg& arg);
    ~WizzrobeSummon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd0
    const int* mSummonBufferSize_s{};
    // static_param at offset 0xd8
    const int* mWeaponIndex_s{};
    // static_param at offset 0xe0
    sead::SafeString mSummonBufferKey_s{};
    // aitree_variable at offset 0xf0
    int* mSummonCount_a{};
};

}  // namespace uking::action
