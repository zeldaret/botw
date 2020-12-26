#pragma once

#include "Game/AI/Action/actionArmorBindAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmArmorBindAction : public ArmorBindAction {
    SEAD_RTTI_OVERRIDE(AnmArmorBindAction, ArmorBindAction)
public:
    explicit AnmArmorBindAction(const InitArg& arg);
    ~AnmArmorBindAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
