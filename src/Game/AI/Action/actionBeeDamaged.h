#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BeeDamaged : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BeeDamaged, ksys::act::ai::Action)
public:
    explicit BeeDamaged(const InitArg& arg);
    ~BeeDamaged() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const float* mSubActorSpeed_s{};
    // static_param at offset 0x30
    const float* mAddYSpeed_s{};
};

}  // namespace uking::action
