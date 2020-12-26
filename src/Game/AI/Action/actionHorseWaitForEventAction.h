#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseWaitForEventAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseWaitForEventAction, ksys::act::ai::Action)
public:
    explicit HorseWaitForEventAction(const InitArg& arg);
    ~HorseWaitForEventAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsAngryEnable_d{};
    // dynamic_param at offset 0x28
    bool* mIsEatEnable_d{};
    // dynamic_param at offset 0x30
    bool* mIsLoveEnable_d{};
    // dynamic_param at offset 0x38
    bool* mHasToCue_d{};
    // dynamic_param at offset 0x40
    bool* mIsNoMorph_d{};
};

}  // namespace uking::action
