#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetOnMovableNavmeshSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetOnMovableNavmeshSelect, ksys::act::ai::Ai)
public:
    explicit TargetOnMovableNavmeshSelect(const InitArg& arg);
    ~TargetOnMovableNavmeshSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCheckDist_s{};
    // static_param at offset 0x40
    const float* mOnStopCheckDist_s{};
};

}  // namespace uking::ai
