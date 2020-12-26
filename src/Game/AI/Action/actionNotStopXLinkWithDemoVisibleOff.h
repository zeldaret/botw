#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NotStopXLinkWithDemoVisibleOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NotStopXLinkWithDemoVisibleOff, ksys::act::ai::Action)
public:
    explicit NotStopXLinkWithDemoVisibleOff(const InitArg& arg);
    ~NotStopXLinkWithDemoVisibleOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
