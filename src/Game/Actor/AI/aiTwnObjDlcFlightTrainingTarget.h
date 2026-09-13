#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TwnObjDlcFlightTrainingTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TwnObjDlcFlightTrainingTarget, ksys::act::ai::Ai)
public:
    explicit TwnObjDlcFlightTrainingTarget(const InitArg& arg);
    ~TwnObjDlcFlightTrainingTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mLimitTime_s{};
};

}  // namespace uking::ai
