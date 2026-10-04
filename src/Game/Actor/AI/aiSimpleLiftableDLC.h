#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SimpleLiftableDLC : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SimpleLiftableDLC, ksys::act::ai::Ai)
public:
    explicit SimpleLiftableDLC(const InitArg& arg);
    ~SimpleLiftableDLC() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mScaleToLiftUp_s{};
};

}  // namespace uking::ai
