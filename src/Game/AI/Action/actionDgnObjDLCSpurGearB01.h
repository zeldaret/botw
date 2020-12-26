#pragma once

#include "Game/AI/Action/actionGearRotate.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DgnObjDLCSpurGearB01 : public GearRotate {
    SEAD_RTTI_OVERRIDE(DgnObjDLCSpurGearB01, GearRotate)
public:
    explicit DgnObjDLCSpurGearB01(const InitArg& arg);
    ~DgnObjDLCSpurGearB01() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
