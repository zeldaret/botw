#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetCurrentDungeonClearFlag : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetCurrentDungeonClearFlag, ksys::act::ai::Action)
public:
    explicit SetCurrentDungeonClearFlag(const InitArg& arg);
    ~SetCurrentDungeonClearFlag() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
