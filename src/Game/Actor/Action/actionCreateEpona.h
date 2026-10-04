#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CreateEpona : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CreateEpona, ksys::act::ai::Action)
public:
    explicit CreateEpona(const InitArg& arg);
    ~CreateEpona() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAreaSearchCharacterRadius_s{};
    // static_param at offset 0x28
    const float* mAreaThreshold_s{};
    // static_param at offset 0x30
    const float* mAreaSearchRadius_s{};
    // static_param at offset 0x38
    const float* mCreateStartRate_s{};
};

}  // namespace uking::action
