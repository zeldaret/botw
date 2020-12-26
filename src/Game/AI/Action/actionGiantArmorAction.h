#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantArmorAction : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(GiantArmorAction, ActionWithPosAngReduce)
public:
    explicit GiantArmorAction(const InitArg& arg);
    ~GiantArmorAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const bool* mUseRestart_s{};
    // static_param at offset 0x38
    sead::SafeString mStartAS_s{};
    // static_param at offset 0x48
    sead::SafeString mLoopAS_s{};
    // static_param at offset 0x58
    sead::SafeString mEndAS_s{};
};

}  // namespace uking::action
