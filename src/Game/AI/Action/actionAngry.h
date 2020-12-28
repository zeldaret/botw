#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Angry : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(Angry, ActionWithAS)
public:
    explicit Angry(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
