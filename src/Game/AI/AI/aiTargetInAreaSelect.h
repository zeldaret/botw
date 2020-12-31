#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetInAreaSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetInAreaSelect, ksys::act::ai::Ai)
public:
    explicit TargetInAreaSelect(const InitArg& arg);
    ~TargetInAreaSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mOption_s{};
};

}  // namespace uking::ai
