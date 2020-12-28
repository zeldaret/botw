#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MarkPosition : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MarkPosition, ksys::act::ai::Action)
public:
    explicit MarkPosition(const InitArg& arg);
    ~MarkPosition() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    float* mPositionX_d{};
    // dynamic_param at offset 0x28
    float* mPositionY_d{};
    // dynamic_param at offset 0x30
    float* mPositionZ_d{};
};

}  // namespace uking::action
