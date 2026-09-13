#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetGameDataStringAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetGameDataStringAction, ksys::act::ai::Action)
public:
    explicit EventSetGameDataStringAction(const InitArg& arg);
    ~EventSetGameDataStringAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataStringName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mValue_d{};
};

}  // namespace uking::action
