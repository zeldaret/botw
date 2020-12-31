#pragma once

#include "Game/AI/AI/aiAttackGraveChase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AttackGraveChaseWithSensor : public AttackGraveChase {
    SEAD_RTTI_OVERRIDE(AttackGraveChaseWithSensor, AttackGraveChase)
public:
    explicit AttackGraveChaseWithSensor(const InitArg& arg);
    ~AttackGraveChaseWithSensor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    sead::SafeString mRigidBodyGroupName_s{};
    // static_param at offset 0x78
    sead::SafeString mRigidBodyName_s{};
};

}  // namespace uking::ai
