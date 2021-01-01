#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetGameDataFloatAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetGameDataFloatAction, ksys::act::ai::Action)
public:
    explicit EventSetGameDataFloatAction(const InitArg& arg);
    ~EventSetGameDataFloatAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    float* mValue_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mGameDataFloatName_d{};
};

}  // namespace uking::action
