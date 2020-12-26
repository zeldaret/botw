#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventTalkEndAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventTalkEndAction, ksys::act::ai::Action)
public:
    explicit EventTalkEndAction(const InitArg& arg);
    ~EventTalkEndAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
