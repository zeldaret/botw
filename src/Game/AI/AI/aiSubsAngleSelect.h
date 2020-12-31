#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SubsAngleSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SubsAngleSelect, ksys::act::ai::Ai)
public:
    explicit SubsAngleSelect(const InitArg& arg);
    ~SubsAngleSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSubsAngle_s{};
    // static_param at offset 0x40
    const bool* mCheckOnce_s{};
    // static_param at offset 0x48
    const bool* mYRotOnly_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
