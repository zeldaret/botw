#pragma once

#include "Game/AI/Action/actionAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BlowOffAttack : public Attack {
    SEAD_RTTI_OVERRIDE(BlowOffAttack, Attack)
public:
    explicit BlowOffAttack(const InitArg& arg);
    ~BlowOffAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
