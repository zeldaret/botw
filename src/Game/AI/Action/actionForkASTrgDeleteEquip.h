#pragma once

#include "Game/AI/Action/actionForkASTrgDelete.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgDeleteEquip : public ForkASTrgDelete {
    SEAD_RTTI_OVERRIDE(ForkASTrgDeleteEquip, ForkASTrgDelete)
public:
    explicit ForkASTrgDeleteEquip(const InitArg& arg);
    ~ForkASTrgDeleteEquip() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
};

}  // namespace uking::action
