#pragma once

#include "Game/AI/Action/actionForkOnEnterSwapDropTableActorBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkOnEnterSwapDropTableActor : public ForkOnEnterSwapDropTableActorBase {
    SEAD_RTTI_OVERRIDE(ForkOnEnterSwapDropTableActor, ForkOnEnterSwapDropTableActorBase)
public:
    explicit ForkOnEnterSwapDropTableActor(const InitArg& arg);
    ~ForkOnEnterSwapDropTableActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    sead::SafeString mTableName_s{};
};

}  // namespace uking::action
