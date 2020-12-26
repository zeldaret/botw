#pragma once

#include "Game/AI/Action/actionAreaActorObserve.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaActorObserveByActorTag : public AreaActorObserve {
    SEAD_RTTI_OVERRIDE(AreaActorObserveByActorTag, AreaActorObserve)
public:
    explicit AreaActorObserveByActorTag(const InitArg& arg);
    ~AreaActorObserveByActorTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x38
    const int* mCount_m{};
    // map_unit_param at offset 0x40
    const bool* mIsSendMessage_m{};
    // map_unit_param at offset 0x48
    const bool* mDefaultBasicSignal_m{};
};

}  // namespace uking::action
