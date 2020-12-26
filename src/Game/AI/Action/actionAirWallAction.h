#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AirWallAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AirWallAction, ksys::act::ai::Action)
public:
    explicit AirWallAction(const InitArg& arg);
    ~AirWallAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
