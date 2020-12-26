#pragma once

#include "Game/AI/Action/actionAirOctaFloatBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AirOctaFloat : public AirOctaFloatBase {
    SEAD_RTTI_OVERRIDE(AirOctaFloat, AirOctaFloatBase)
public:
    explicit AirOctaFloat(const InitArg& arg);
    ~AirOctaFloat() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
