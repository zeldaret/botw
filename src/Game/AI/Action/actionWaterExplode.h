#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterExplode : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaterExplode, ksys::act::ai::Action)
public:
    explicit WaterExplode(const InitArg& arg);
    ~WaterExplode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRadius_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
};

}  // namespace uking::action
