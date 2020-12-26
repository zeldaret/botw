#pragma once

#include "Game/AI/Action/actionForkGanonBeastWeakPoint.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkGanonBeastWeakPointOn : public ForkGanonBeastWeakPoint {
    SEAD_RTTI_OVERRIDE(ForkGanonBeastWeakPointOn, ForkGanonBeastWeakPoint)
public:
    explicit ForkGanonBeastWeakPointOn(const InitArg& arg);
    ~ForkGanonBeastWeakPointOn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
