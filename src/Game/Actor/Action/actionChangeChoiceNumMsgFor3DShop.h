#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChangeChoiceNumMsgFor3DShop : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChangeChoiceNumMsgFor3DShop, ksys::act::ai::Action)
public:
    explicit ChangeChoiceNumMsgFor3DShop(const InitArg& arg);
    ~ChangeChoiceNumMsgFor3DShop() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
