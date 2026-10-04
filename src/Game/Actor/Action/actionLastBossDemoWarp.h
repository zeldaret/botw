#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossDemoWarp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossDemoWarp, ksys::act::ai::Action)
public:
    explicit LastBossDemoWarp(const InitArg& arg);
    ~LastBossDemoWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mWarpTime_s{};
    // static_param at offset 0x28
    const bool* mIsUpdateHomePos_s{};
    // static_param at offset 0x30
    sead::SafeString mWarpAnchorUniqName_s{};
};

}  // namespace uking::action
