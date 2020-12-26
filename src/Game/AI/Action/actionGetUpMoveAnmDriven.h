#pragma once

#include "Game/AI/Action/actionGetUp.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetUpMoveAnmDriven : public GetUp {
    SEAD_RTTI_OVERRIDE(GetUpMoveAnmDriven, GetUp)
public:
    explicit GetUpMoveAnmDriven(const InitArg& arg);
    ~GetUpMoveAnmDriven() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x160
    sead::SafeString mTargetBoneName_s{};
};

}  // namespace uking::action
