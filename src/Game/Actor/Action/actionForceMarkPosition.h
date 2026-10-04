#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceMarkPosition : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForceMarkPosition, ksys::act::ai::Action)
public:
    explicit ForceMarkPosition(const InitArg& arg);
    ~ForceMarkPosition() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mPinColorIdx_d{};
};

}  // namespace uking::action
