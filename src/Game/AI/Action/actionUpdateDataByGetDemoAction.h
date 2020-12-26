#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class UpdateDataByGetDemoAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(UpdateDataByGetDemoAction, ksys::act::ai::Action)
public:
    explicit UpdateDataByGetDemoAction(const InitArg& arg);
    ~UpdateDataByGetDemoAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
