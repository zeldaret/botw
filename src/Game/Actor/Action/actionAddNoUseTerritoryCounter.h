#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AddNoUseTerritoryCounter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AddNoUseTerritoryCounter, ksys::act::ai::Action)
public:
    explicit AddNoUseTerritoryCounter(const InitArg& arg);
    ~AddNoUseTerritoryCounter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mCounter_s{};
    // static_param at offset 0x28
    const float* mCamDist_s{};
    // map_unit_param at offset 0x30
    const float* mTerritoryArea_m{};
    // aitree_variable at offset 0x38
    bool* mIsUseTerritory_a{};
};

}  // namespace uking::action
