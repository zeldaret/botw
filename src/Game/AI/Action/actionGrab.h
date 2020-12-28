#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Grab : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(Grab, ActionWithPosAngReduce)
public:
    explicit Grab(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mGrabIdx_s{};
    // static_param at offset 0x38
    const float* mCheckRadius_s{};
    // static_param at offset 0x40
    const float* mCheckSpeed_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mAttOffset_s{};
};

}  // namespace uking::action
