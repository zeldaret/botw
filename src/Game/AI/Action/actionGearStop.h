#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GearStop : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GearStop, ksys::act::ai::Action)
public:
    explicit GearStop(const InitArg& arg);
    ~GearStop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mDgnRotDir_m{};
    // map_unit_param at offset 0x28
    const float* mRotateDamp_m{};
};

}  // namespace uking::action
