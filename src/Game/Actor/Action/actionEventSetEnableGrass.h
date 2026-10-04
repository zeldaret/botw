#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetEnableGrass : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetEnableGrass, ksys::act::ai::Action)
public:
    explicit EventSetEnableGrass(const InitArg& arg);
    ~EventSetEnableGrass() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mEnable_d{};
};

}  // namespace uking::action
