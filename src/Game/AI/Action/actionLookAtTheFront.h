#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LookAtTheFront : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LookAtTheFront, ksys::act::ai::Action)
public:
    explicit LookAtTheFront(const InitArg& arg);
    ~LookAtTheFront() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mIsValid_d{};
};

}  // namespace uking::action
