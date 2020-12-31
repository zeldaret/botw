#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalEnemyBlownOff : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalEnemyBlownOff, ksys::act::ai::Ai)
public:
    explicit StalEnemyBlownOff(const InitArg& arg);
    ~StalEnemyBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDrownDepth_s{};
};

}  // namespace uking::ai
