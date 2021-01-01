#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetGameDataIntAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetGameDataIntAction, ksys::act::ai::Action)
public:
    explicit EventSetGameDataIntAction(const InitArg& arg);
    ~EventSetGameDataIntAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mValue_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mGameDataIntName_d{};
};

}  // namespace uking::action
