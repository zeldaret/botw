#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeaponEquipedAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponEquipedAI, ksys::act::ai::Ai)
public:
    explicit WeaponEquipedAI(const InitArg& arg);
    ~WeaponEquipedAI() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::ai
