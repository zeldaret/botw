#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShelterFromRain : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(ShelterFromRain, AreaTagAction)
public:
    explicit ShelterFromRain(const InitArg& arg);
    ~ShelterFromRain() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x38
    const int* mShelterFromRainTagType_m{};
};

}  // namespace uking::action
