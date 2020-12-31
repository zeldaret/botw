#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ReflectableEscape : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ReflectableEscape, ksys::act::ai::Ai)
public:
    explicit ReflectableEscape(const InitArg& arg);
    ~ReflectableEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mEscapeDist_s{};
    // static_param at offset 0x40
    const float* mNearDist_s{};
    // static_param at offset 0x48
    const float* mEscapeTimer_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
