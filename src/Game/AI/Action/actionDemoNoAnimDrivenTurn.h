#pragma once

#include "Game/AI/Action/actionForkTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoNoAnimDrivenTurn : public ForkTurn {
    SEAD_RTTI_OVERRIDE(DemoNoAnimDrivenTurn, ForkTurn)
public:
    explicit DemoNoAnimDrivenTurn(const InitArg& arg);
    ~DemoNoAnimDrivenTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xc0
    int* mObjectId_d{};
    // dynamic_param at offset 0xc8
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0xd8
    sead::SafeString mUniqueName_d{};
};

}  // namespace uking::action
