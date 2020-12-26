#pragma once

#include "Game/AI/Action/actionGetItem.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetWeaponEquip : public GetItem {
    SEAD_RTTI_OVERRIDE(GetWeaponEquip, GetItem)
public:
    explicit GetWeaponEquip(const InitArg& arg);
    ~GetWeaponEquip() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
