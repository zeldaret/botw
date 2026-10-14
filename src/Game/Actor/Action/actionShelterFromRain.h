#pragma once

#include "Game/Actor/Area/Action/actionAreaActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShelterFromRain : public AreaActionBase {
    SEAD_RTTI_OVERRIDE(ShelterFromRain, AreaActionBase)
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
