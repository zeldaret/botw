#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerEquipNearMasterSword : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerEquipNearMasterSword, ksys::act::ai::Action)
public:
    explicit PlayerEquipNearMasterSword(const InitArg& arg);
    ~PlayerEquipNearMasterSword() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
