#pragma once

#include "Game/AI/Action/actionWaterFloatImmobile.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterFloatFreeze : public WaterFloatImmobile {
    SEAD_RTTI_OVERRIDE(WaterFloatFreeze, WaterFloatImmobile)
public:
    explicit WaterFloatFreeze(const InitArg& arg);
    ~WaterFloatFreeze() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x70
    bool* mIsKeepFreeze_a{};
};

}  // namespace uking::action
