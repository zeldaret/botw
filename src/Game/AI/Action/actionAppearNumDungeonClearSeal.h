#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AppearNumDungeonClearSeal : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AppearNumDungeonClearSeal, ksys::act::ai::Action)
public:
    explicit AppearNumDungeonClearSeal(const InitArg& arg);
    ~AppearNumDungeonClearSeal() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
