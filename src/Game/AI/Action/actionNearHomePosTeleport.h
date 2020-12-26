#pragma once

#include "Game/AI/Action/actionLandTeleport.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NearHomePosTeleport : public LandTeleport {
    SEAD_RTTI_OVERRIDE(NearHomePosTeleport, LandTeleport)
public:
    explicit NearHomePosTeleport(const InitArg& arg);
    ~NearHomePosTeleport() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
