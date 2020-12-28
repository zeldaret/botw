#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceEndPlayerSlow : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForceEndPlayerSlow, ksys::act::ai::Action)
public:
    explicit ForceEndPlayerSlow(const InitArg& arg);
    ~ForceEndPlayerSlow() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
