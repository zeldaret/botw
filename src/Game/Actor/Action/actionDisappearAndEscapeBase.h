#pragma once

#include "Game/Actor/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DisappearAndEscapeBase : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(DisappearAndEscapeBase, ActionWithAS)
public:
    explicit DisappearAndEscapeBase(const InitArg& arg);
    ~DisappearAndEscapeBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
