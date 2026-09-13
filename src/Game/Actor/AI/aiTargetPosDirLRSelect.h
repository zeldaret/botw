#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosDirLRSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetPosDirLRSelect, ksys::act::ai::Ai)
public:
    explicit TargetPosDirLRSelect(const InitArg& arg);
    ~TargetPosDirLRSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsCheckEveryFrame_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
