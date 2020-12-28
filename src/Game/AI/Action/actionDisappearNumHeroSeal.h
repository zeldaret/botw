#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DisappearNumHeroSeal : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DisappearNumHeroSeal, ksys::act::ai::Action)
public:
    explicit DisappearNumHeroSeal(const InitArg& arg);
    ~DisappearNumHeroSeal() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
