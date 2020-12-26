#pragma once

#include "Game/AI/Action/actionWaterFloatFreeze.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceGetUpWaterFloatFreeze : public WaterFloatFreeze {
    SEAD_RTTI_OVERRIDE(ForceGetUpWaterFloatFreeze, WaterFloatFreeze)
public:
    explicit ForceGetUpWaterFloatFreeze(const InitArg& arg);
    ~ForceGetUpWaterFloatFreeze() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
