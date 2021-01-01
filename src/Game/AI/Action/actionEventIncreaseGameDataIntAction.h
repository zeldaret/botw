#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventIncreaseGameDataIntAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventIncreaseGameDataIntAction, ksys::act::ai::Action)
public:
    explicit EventIncreaseGameDataIntAction(const InitArg& arg);
    ~EventIncreaseGameDataIntAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mValue_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mGameDataIntName_d{};
};

}  // namespace uking::action
