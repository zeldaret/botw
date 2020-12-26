#pragma once

#include "Game/AI/Action/actionBindAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantArmorEquip : public BindAction {
    SEAD_RTTI_OVERRIDE(GiantArmorEquip, BindAction)
public:
    explicit GiantArmorEquip(const InitArg& arg);
    ~GiantArmorEquip() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
