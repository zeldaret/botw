#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddCarriedBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AddCarriedBase, ksys::act::ai::Ai)
public:
    explicit AddCarriedBase(const InitArg& arg);
    ~AddCarriedBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFailDistance_s{};
    // static_param at offset 0x40
    const bool* mIsRecoverCharCtrlAxis_s{};
    // static_param at offset 0x48
    const bool* mIsUseConstraint_s{};
    // static_param at offset 0x50
    sead::SafeString mHoldOnXLinkKey_s{};
};

}  // namespace uking::ai
