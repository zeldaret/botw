#pragma once

#include "Game/AI/Action/actionEquipedAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedWithScale : public EquipedAction {
    SEAD_RTTI_OVERRIDE(EquipedWithScale, EquipedAction)
public:
    explicit EquipedWithScale(const InitArg& arg);
    ~EquipedWithScale() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
