#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ListenerSetModeAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ListenerSetModeAction, ksys::act::ai::Action)
public:
    explicit ListenerSetModeAction(const InitArg& arg);
    ~ListenerSetModeAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString* mMode_d{};
};

}  // namespace uking::action
