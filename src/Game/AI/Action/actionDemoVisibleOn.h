#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoVisibleOn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoVisibleOn, ksys::act::ai::Action)
public:
    explicit DemoVisibleOn(const InitArg& arg);
    ~DemoVisibleOn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
