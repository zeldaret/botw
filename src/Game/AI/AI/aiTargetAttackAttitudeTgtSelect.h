#pragma once

#include "Game/AI/AI/aiTargetAttackAttitudeTgtSelectBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetAttackAttitudeTgtSelect : public TargetAttackAttitudeTgtSelectBase {
    SEAD_RTTI_OVERRIDE(TargetAttackAttitudeTgtSelect, TargetAttackAttitudeTgtSelectBase)
public:
    explicit TargetAttackAttitudeTgtSelect(const InitArg& arg);
    ~TargetAttackAttitudeTgtSelect() override;

    void loadParams_() override;

protected:
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
