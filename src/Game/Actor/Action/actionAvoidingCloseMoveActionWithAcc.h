#pragma once

#include "Game/Actor/Action/actionAvoidingCloseMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AvoidingCloseMoveActionWithAcc : public AvoidingCloseMoveBase {
    SEAD_RTTI_OVERRIDE(AvoidingCloseMoveActionWithAcc, AvoidingCloseMoveBase)
public:
    explicit AvoidingCloseMoveActionWithAcc(const InitArg& arg);
    ~AvoidingCloseMoveActionWithAcc() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x98
    const float* mAccRatio_s{};
};

}  // namespace uking::action
