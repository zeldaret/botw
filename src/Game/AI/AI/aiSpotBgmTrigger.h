#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SpotBgmTrigger : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SpotBgmTrigger, ksys::act::ai::Ai)
public:
    explicit SpotBgmTrigger(const InitArg& arg);
    ~SpotBgmTrigger() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsStopWithoutReductionY_m{};
    // map_unit_param at offset 0x40
    sead::SafeString mSound_m{};
};

}  // namespace uking::ai
