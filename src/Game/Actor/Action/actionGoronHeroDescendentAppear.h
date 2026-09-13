#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GoronHeroDescendentAppear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GoronHeroDescendentAppear, ksys::act::ai::Action)
public:
    explicit GoronHeroDescendentAppear(const InitArg& arg);
    ~GoronHeroDescendentAppear() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
