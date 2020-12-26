#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShootArrow : public ActionEx {
    SEAD_RTTI_OVERRIDE(ShootArrow, ActionEx)
public:
    explicit ShootArrow(const InitArg& arg);
    ~ShootArrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
