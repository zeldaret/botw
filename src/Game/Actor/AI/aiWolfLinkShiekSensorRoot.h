#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkShiekSensorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkShiekSensorRoot, ksys::act::ai::Ai)
public:
    explicit WolfLinkShiekSensorRoot(const InitArg& arg);
    ~WolfLinkShiekSensorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDistanceUntilUpdateTarget_s{};
    // dynamic_param at offset 0x40
    bool* mUpdateTarget_d{};
};

}  // namespace uking::ai
