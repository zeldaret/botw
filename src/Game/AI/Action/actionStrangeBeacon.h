#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StrangeBeacon : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StrangeBeacon, ksys::act::ai::Action)
public:
    explicit StrangeBeacon(const InitArg& arg);
    ~StrangeBeacon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mSaveFlag_s{};
    // static_param at offset 0x30
    sead::SafeString mCalcStartFlag_s{};
    // static_param at offset 0x40
    sead::SafeString mKeyName_s{};
};

}  // namespace uking::action
