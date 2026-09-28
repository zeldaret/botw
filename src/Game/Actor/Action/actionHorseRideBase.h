#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseRideBase, ksys::act::ai::Action)
public:
    explicit HorseRideBase(const InitArg& arg);
    ~HorseRideBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mUpperBodyASSlot_s{};
    // static_param at offset 0x28
    const int* mLowerBodyASSlot_s{};
};

}  // namespace uking::action
