#pragma once

#include "Game/AI/Action/actionSimpleLineBeam.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniLineBeam : public SimpleLineBeam {
    SEAD_RTTI_OVERRIDE(GuardianMiniLineBeam, SimpleLineBeam)
public:
    explicit GuardianMiniLineBeam(const InitArg& arg);
    ~GuardianMiniLineBeam() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const int* mIceBlockBreakTime_s{};
};

}  // namespace uking::action
