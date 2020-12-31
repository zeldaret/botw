#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalEnemyChasePart : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalEnemyChasePart, ksys::act::ai::Ai)
public:
    explicit StalEnemyChasePart(const InitArg& arg);
    ~StalEnemyChasePart() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    bool* mIsCarried_d{};
    // dynamic_param at offset 0x40
    bool* mIsCarriedByPlayer_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
