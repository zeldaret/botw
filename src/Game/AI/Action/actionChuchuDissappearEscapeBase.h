#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChuchuDissappearEscapeBase : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(ChuchuDissappearEscapeBase, ActionWithAS)
public:
    explicit ChuchuDissappearEscapeBase(const InitArg& arg);
    ~ChuchuDissappearEscapeBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
