#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IncreaseNumHeroSeal : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(IncreaseNumHeroSeal, ksys::act::ai::Action)
public:
    explicit IncreaseNumHeroSeal(const InitArg& arg);
    ~IncreaseNumHeroSeal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mRelicPattern_d{};
    // dynamic_param at offset 0x28
    int* mValue_d{};
};

}  // namespace uking::action
