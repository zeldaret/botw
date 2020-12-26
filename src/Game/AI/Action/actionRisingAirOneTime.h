#pragma once

#include "Game/AI/Action/actionAscendingCurrent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RisingAirOneTime : public AscendingCurrent {
    SEAD_RTTI_OVERRIDE(RisingAirOneTime, AscendingCurrent)
public:
    explicit RisingAirOneTime(const InitArg& arg);
    ~RisingAirOneTime() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    const float* mLostCounter_s{};
};

}  // namespace uking::action
