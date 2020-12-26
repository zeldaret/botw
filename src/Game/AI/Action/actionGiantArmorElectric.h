#pragma once

#include "Game/AI/Action/actionGiantArmorAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantArmorElectric : public GiantArmorAction {
    SEAD_RTTI_OVERRIDE(GiantArmorElectric, GiantArmorAction)
public:
    explicit GiantArmorElectric(const InitArg& arg);
    ~GiantArmorElectric() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const int* mTimeMin_s{};
};

}  // namespace uking::action
