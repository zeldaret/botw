#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventMiniGameFinish : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventMiniGameFinish, ksys::act::ai::Action)
public:
    explicit EventMiniGameFinish(const InitArg& arg);
    ~EventMiniGameFinish() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mTextType_d{};
};

}  // namespace uking::action
