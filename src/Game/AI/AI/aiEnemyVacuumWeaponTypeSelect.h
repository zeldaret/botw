#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyVacuumWeaponTypeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyVacuumWeaponTypeSelect, ksys::act::ai::Ai)
public:
    explicit EnemyVacuumWeaponTypeSelect(const InitArg& arg);
    ~EnemyVacuumWeaponTypeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mPartsKey_s{};
};

}  // namespace uking::ai
