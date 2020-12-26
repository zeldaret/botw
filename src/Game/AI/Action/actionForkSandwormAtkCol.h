#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSandwormAtkCol : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkSandwormAtkCol, ksys::act::ai::Action)
public:
    explicit ForkSandwormAtkCol(const InitArg& arg);
    ~ForkSandwormAtkCol() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mMinDamage_s{};
    // static_param at offset 0x28
    const bool* mIsUseTossAt_s{};
    // static_param at offset 0x30
    const bool* mIsColNoHitPlayer_s{};
};

}  // namespace uking::action
