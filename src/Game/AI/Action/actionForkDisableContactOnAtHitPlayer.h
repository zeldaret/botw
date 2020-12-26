#pragma once

#include "Game/AI/Action/actionForkDisableContact.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkDisableContactOnAtHitPlayer : public ForkDisableContact {
    SEAD_RTTI_OVERRIDE(ForkDisableContactOnAtHitPlayer, ForkDisableContact)
public:
    explicit ForkDisableContactOnAtHitPlayer(const InitArg& arg);
    ~ForkDisableContactOnAtHitPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
