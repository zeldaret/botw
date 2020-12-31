#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GiantStoneShootAngrySelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GiantStoneShootAngrySelect, ksys::act::ai::Ai)
public:
    explicit GiantStoneShootAngrySelect(const InitArg& arg);
    ~GiantStoneShootAngrySelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mThrowableAngryRate_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcHandle** mIgniteHandle_d{};
};

}  // namespace uking::ai
