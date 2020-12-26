#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SoundShieldingAreaTagAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(SoundShieldingAreaTagAction, AreaTagAction)
public:
    explicit SoundShieldingAreaTagAction(const InitArg& arg);
    ~SoundShieldingAreaTagAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x38
    const float* mMerginDistance_m{};
    // map_unit_param at offset 0x40
    const bool* mIsShieldChemicalWind_m{};
};

}  // namespace uking::action
