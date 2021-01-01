#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventMiniGameTimerWrite : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventMiniGameTimerWrite, ksys::act::ai::Action)
public:
    explicit EventMiniGameTimerWrite(const InitArg& arg);
    ~EventMiniGameTimerWrite() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataIntNameMintues_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataIntNameSeconds_d{};
    // dynamic_param at offset 0x40
    sead::SafeString mGameDataIntNameMiliseconds_d{};
};

}  // namespace uking::action
