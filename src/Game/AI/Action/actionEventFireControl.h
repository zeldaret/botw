#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventFireControl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventFireControl, ksys::act::ai::Action)
public:
    explicit EventFireControl(const InitArg& arg);
    ~EventFireControl() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mReleaseFire_d{};
};

}  // namespace uking::action
