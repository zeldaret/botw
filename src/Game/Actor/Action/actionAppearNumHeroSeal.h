#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AppearNumHeroSeal : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AppearNumHeroSeal, ksys::act::ai::Action)
public:
    explicit AppearNumHeroSeal(const InitArg& arg);
    ~AppearNumHeroSeal() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mRelicPattern_d{};
};

}  // namespace uking::action
