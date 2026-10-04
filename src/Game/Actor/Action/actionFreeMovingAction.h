#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FreeMovingAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FreeMovingAction, ksys::act::ai::Action)
public:
    explicit FreeMovingAction(const InitArg& arg);
    ~FreeMovingAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
