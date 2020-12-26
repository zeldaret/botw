#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MotorcycleWaitForEvent : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MotorcycleWaitForEvent, ksys::act::ai::Action)
public:
    explicit MotorcycleWaitForEvent(const InitArg& arg);
    ~MotorcycleWaitForEvent() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
