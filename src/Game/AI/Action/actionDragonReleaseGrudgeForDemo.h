#pragma once

#include "Game/AI/Action/actionDragonPlayASForDemo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DragonReleaseGrudgeForDemo : public DragonPlayASForDemo {
    SEAD_RTTI_OVERRIDE(DragonReleaseGrudgeForDemo, DragonPlayASForDemo)
public:
    explicit DragonReleaseGrudgeForDemo(const InitArg& arg);
    ~DragonReleaseGrudgeForDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const int* mReleaseTime_s{};
    // static_param at offset 0xc8
    const int* mHeadTransSmoothStartFrame_s{};
    // static_param at offset 0xd0
    const int* mHeadTransSmoothEndFrame_s{};
    // static_param at offset 0xd8
    const float* mHeadTransSmoothRate_s{};
    // static_param at offset 0xe0
    const float* mHeadTransSmoothSklRootRate_s{};
};

}  // namespace uking::action
