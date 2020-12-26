#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkLodNoCountTimer : public Fork {
    SEAD_RTTI_OVERRIDE(ForkLodNoCountTimer, Fork)
public:
    explicit ForkLodNoCountTimer(const InitArg& arg);
    ~ForkLodNoCountTimer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWaitFrame_s{};
    // static_param at offset 0x38
    const int* mWaitFrameRand_s{};
    // static_param at offset 0x40
    const float* mCamDist_s{};
    // static_param at offset 0x48
    const bool* mIsTrgStart_s{};
};

}  // namespace uking::action
