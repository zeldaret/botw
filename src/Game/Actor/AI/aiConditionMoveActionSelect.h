#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ConditionMoveActionSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ConditionMoveActionSelect, ksys::act::ai::Ai)
public:
    explicit ConditionMoveActionSelect(const InitArg& arg);
    ~ConditionMoveActionSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mCheckLineReachable_s{};
    // dynamic_param at offset 0x40
    float* mDistanceKept_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x50
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
