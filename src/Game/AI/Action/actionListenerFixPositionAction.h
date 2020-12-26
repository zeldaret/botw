#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ListenerFixPositionAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ListenerFixPositionAction, ksys::act::ai::Action)
public:
    explicit ListenerFixPositionAction(const InitArg& arg);
    ~ListenerFixPositionAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString* mFixType_d{};
};

}  // namespace uking::action
