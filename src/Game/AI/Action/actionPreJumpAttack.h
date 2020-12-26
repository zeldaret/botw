#pragma once

#include "Game/AI/Action/actionPreAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PreJumpAttack : public PreAttack {
    SEAD_RTTI_OVERRIDE(PreJumpAttack, PreAttack)
public:
    explicit PreJumpAttack(const InitArg& arg);
    ~PreJumpAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
