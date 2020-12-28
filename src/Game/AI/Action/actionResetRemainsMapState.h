#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ResetRemainsMapState : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ResetRemainsMapState, ksys::act::ai::Action)
public:
    explicit ResetRemainsMapState(const InitArg& arg);
    ~ResetRemainsMapState() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
