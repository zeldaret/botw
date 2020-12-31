#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BirdEscape : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BirdEscape, ksys::act::ai::Ai)
public:
    explicit BirdEscape(const InitArg& arg);
    ~BirdEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mForceEndTimer_s{};
    // static_param at offset 0x40
    const bool* mIsUseEscapeBefore_s{};
    // static_param at offset 0x48
    const bool* mIsUseEscapeEnd_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    // map_unit_param at offset 0x58
    const bool* mIsLocatorCreate_m{};
};

}  // namespace uking::ai
