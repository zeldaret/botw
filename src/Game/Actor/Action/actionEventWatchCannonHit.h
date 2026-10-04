#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventWatchCannonHit : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventWatchCannonHit, ksys::act::ai::Action)
public:
    explicit EventWatchCannonHit(const InitArg& arg);
    ~EventWatchCannonHit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mWatchFrame_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mXLinkKey_d{};
};

}  // namespace uking::action
