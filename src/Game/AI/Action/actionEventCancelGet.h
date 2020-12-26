#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventCancelGet : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventCancelGet, ksys::act::ai::Action)
public:
    explicit EventCancelGet(const InitArg& arg);
    ~EventCancelGet() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
