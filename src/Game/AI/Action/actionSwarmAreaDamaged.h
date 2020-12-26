#pragma once

#include "Game/AI/Action/actionSwarmDamagedBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwarmAreaDamaged : public SwarmDamagedBase {
    SEAD_RTTI_OVERRIDE(SwarmAreaDamaged, SwarmDamagedBase)
public:
    explicit SwarmAreaDamaged(const InitArg& arg);
    ~SwarmAreaDamaged() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x1b8
    const int* mDeadSubActorMax_s{};
};

}  // namespace uking::action
