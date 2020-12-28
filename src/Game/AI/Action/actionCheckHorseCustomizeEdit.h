#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CheckHorseCustomizeEdit : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CheckHorseCustomizeEdit, ksys::act::ai::Action)
public:
    explicit CheckHorseCustomizeEdit(const InitArg& arg);
    ~CheckHorseCustomizeEdit() override;

protected:
};

}  // namespace uking::action
