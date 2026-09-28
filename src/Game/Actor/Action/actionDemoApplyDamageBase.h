#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoApplyDamageBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoApplyDamageBase, ksys::act::ai::Action)
public:
    explicit DemoApplyDamageBase(const InitArg& arg);
    ~DemoApplyDamageBase() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mValue_d{};
};

}  // namespace uking::action
