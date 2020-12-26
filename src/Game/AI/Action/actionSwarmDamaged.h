#pragma once

#include "Game/AI/Action/actionSwarmDamagedBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwarmDamaged : public SwarmDamagedBase {
    SEAD_RTTI_OVERRIDE(SwarmDamaged, SwarmDamagedBase)
public:
    explicit SwarmDamaged(const InitArg& arg);
    ~SwarmDamaged() override;

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
