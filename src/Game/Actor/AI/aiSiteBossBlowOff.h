#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossBlowOff : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossBlowOff, ksys::act::ai::Ai)
public:
    explicit SiteBossBlowOff(const InitArg& arg);
    ~SiteBossBlowOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    bool* mIsPlayDamageAnm_d{};
};

}  // namespace uking::ai
