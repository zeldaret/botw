#pragma once

#include "Game/Actor/Area/Action/actionAreaActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaActorObserve : public AreaActionBase {
    SEAD_RTTI_OVERRIDE(AreaActorObserve, AreaActionBase)
public:
    explicit AreaActorObserve(const InitArg& arg);
    ~AreaActorObserve() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mCount_m{};
    // map_unit_param at offset 0x40
    const bool* mIsSendMessage_m{};
    // map_unit_param at offset 0x48
    const bool* mDefaultBasicSignal_m{};
};

}  // namespace uking::action
