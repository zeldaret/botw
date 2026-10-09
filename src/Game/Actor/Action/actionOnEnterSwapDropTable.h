#pragma once

#include "Game/Actor/Action/actionOnEnterSwapActorBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnEnterSwapDropTable : public OnEnterSwapActorBase {
    SEAD_RTTI_OVERRIDE(OnEnterSwapDropTable, OnEnterSwapActorBase)
public:
    explicit OnEnterSwapDropTable(const InitArg& arg);
    ~OnEnterSwapDropTable() override;

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
