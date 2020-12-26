#pragma once

#include "Game/AI/Action/actionSmallDamageBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CapturedActKnockBack : public SmallDamageBase {
    SEAD_RTTI_OVERRIDE(CapturedActKnockBack, SmallDamageBase)
public:
    explicit CapturedActKnockBack(const InitArg& arg);
    ~CapturedActKnockBack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
