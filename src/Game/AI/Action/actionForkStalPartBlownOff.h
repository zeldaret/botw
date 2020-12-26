#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkStalPartBlownOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkStalPartBlownOff, ksys::act::ai::Action)
public:
    explicit ForkStalPartBlownOff(const InitArg& arg);
    ~ForkStalPartBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mShootParts_s{};
    // static_param at offset 0x28
    const float* mShootSpeed_s{};
    // static_param at offset 0x30
    const float* mLifeRate_s{};
    // static_param at offset 0x38
    sead::SafeString mBaseNodeName_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mShootDir_s{};
};

}  // namespace uking::action
