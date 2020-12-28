#pragma once

#include "Game/AI/Action/actionGrab.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GrabAttack : public Grab {
    SEAD_RTTI_OVERRIDE(GrabAttack, Grab)
public:
    explicit GrabAttack(const InitArg& arg);
    ~GrabAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    sead::SafeString mASName_s{};
    // static_param at offset 0x60
    sead::SafeString mAtRigidBodyName_s{};
};

}  // namespace uking::action
