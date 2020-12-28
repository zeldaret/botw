#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventUpdateMiniGameBestScore : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventUpdateMiniGameBestScore, ksys::act::ai::Action)
public:
    explicit EventUpdateMiniGameBestScore(const InitArg& arg);
    ~EventUpdateMiniGameBestScore() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mType_d{};
};

}  // namespace uking::action
