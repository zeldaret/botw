#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetFixed : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetFixed, ksys::act::ai::Action)
public:
    explicit EventSetFixed(const InitArg& arg);
    ~EventSetFixed() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x20
    bool* mIsChangeToFixedInDemo_a{};
};

}  // namespace uking::action
