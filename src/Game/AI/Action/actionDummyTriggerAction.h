#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DummyTriggerAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DummyTriggerAction, ksys::act::ai::Action)
public:
    explicit DummyTriggerAction(const InitArg& arg);
    ~DummyTriggerAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
