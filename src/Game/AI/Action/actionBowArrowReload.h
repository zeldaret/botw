#pragma once

#include "Game/AI/Action/actionBindAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowArrowReload : public BindAction {
    SEAD_RTTI_OVERRIDE(BowArrowReload, BindAction)
public:
    explicit BowArrowReload(const InitArg& arg);
    ~BowArrowReload() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
