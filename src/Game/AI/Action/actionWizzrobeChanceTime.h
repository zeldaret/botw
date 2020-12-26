#pragma once

#include "Game/AI/Action/actionHoverBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WizzrobeChanceTime : public HoverBase {
    SEAD_RTTI_OVERRIDE(WizzrobeChanceTime, HoverBase)
public:
    explicit WizzrobeChanceTime(const InitArg& arg);
    ~WizzrobeChanceTime() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x40
    const float* mDefaultCounter_s{};
    // static_param at offset 0x48
    const float* mDamageCounter_s{};
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
