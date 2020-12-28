#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ResetPlayerPullSwordStartLife : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ResetPlayerPullSwordStartLife, ksys::act::ai::Action)
public:
    explicit ResetPlayerPullSwordStartLife(const InitArg& arg);
    ~ResetPlayerPullSwordStartLife() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
