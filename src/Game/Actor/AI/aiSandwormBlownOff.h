#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormBlownOff : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormBlownOff, ksys::act::ai::Ai)
public:
    explicit SandwormBlownOff(const InitArg& arg);
    ~SandwormBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mBlownOffTimer_s{};
};

}  // namespace uking::ai
