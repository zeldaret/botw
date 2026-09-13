#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkGolemMaterialASPlay : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkGolemMaterialASPlay, ksys::act::ai::Action)
public:
    explicit ForkGolemMaterialASPlay(const InitArg& arg);
    ~ForkGolemMaterialASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTargetPartType_s{};
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
    // aitree_variable at offset 0x38
    void* mGolemChemicalController_a{};
};

}  // namespace uking::action
