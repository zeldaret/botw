#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonFarAttackRootOnWall : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonFarAttackRootOnWall, ksys::act::ai::Ai)
public:
    explicit GanonFarAttackRootOnWall(const InitArg& arg);
    ~GanonFarAttackRootOnWall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mPillarMax_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mViewPos_d{};
};

}  // namespace uking::ai
