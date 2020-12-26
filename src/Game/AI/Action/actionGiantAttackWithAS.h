#pragma once

#include "Game/AI/Action/actionGiantAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantAttackWithAS : public GiantAttack {
    SEAD_RTTI_OVERRIDE(GiantAttackWithAS, GiantAttack)
public:
    explicit GiantAttackWithAS(const InitArg& arg);
    ~GiantAttackWithAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x128
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
