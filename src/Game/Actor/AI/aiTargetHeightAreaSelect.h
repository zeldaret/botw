#pragma once

#include "Game/Actor/AI/aiTargetInAreaSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetHeightAreaSelect : public TargetInAreaSelect {
    SEAD_RTTI_OVERRIDE(TargetHeightAreaSelect, TargetInAreaSelect)
public:
    explicit TargetHeightAreaSelect(const InitArg& arg);
    ~TargetHeightAreaSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mHeight_s{};
};

}  // namespace uking::ai
