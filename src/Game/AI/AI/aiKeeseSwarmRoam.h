#pragma once

#include "Game/AI/AI/aiCircleMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeeseSwarmRoam : public CircleMove {
    SEAD_RTTI_OVERRIDE(KeeseSwarmRoam, CircleMove)
public:
    explicit KeeseSwarmRoam(const InitArg& arg);
    ~KeeseSwarmRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x60
    sead::Vector3f* mCentralPos_d{};
};

}  // namespace uking::ai
