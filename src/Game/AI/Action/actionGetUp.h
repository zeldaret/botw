#pragma once

#include "Game/AI/Action/actionGetUpBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetUp : public GetUpBase {
    SEAD_RTTI_OVERRIDE(GetUp, GetUpBase)
public:
    explicit GetUp(const InitArg& arg);
    ~GetUp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x148
    const float* mRotRatio_s{};
};

}  // namespace uking::action
