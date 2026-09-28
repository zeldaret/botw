#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::snd {

class EventBgmCtrlAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventBgmCtrlAction, ksys::act::ai::Action)
public:
    explicit EventBgmCtrlAction(const InitArg& arg);
    ~EventBgmCtrlAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mCtrlType_d{};
};

}  // namespace ksys::snd
