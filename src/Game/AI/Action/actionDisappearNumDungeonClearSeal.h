#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DisappearNumDungeonClearSeal : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DisappearNumDungeonClearSeal, ksys::act::ai::Action)
public:
    explicit DisappearNumDungeonClearSeal(const InitArg& arg);
    ~DisappearNumDungeonClearSeal() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
