#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonShockRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonShockRoot, ksys::act::ai::Ai)
public:
    explicit GanonShockRoot(const InitArg& arg);
    ~GanonShockRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsDoRecoverAction_s{};
    // static_param at offset 0x40
    const bool* mIsGuardJust_s{};
};

}  // namespace uking::ai
