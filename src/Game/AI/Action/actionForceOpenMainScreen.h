#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceOpenMainScreen : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForceOpenMainScreen, ksys::act::ai::Action)
public:
    explicit ForceOpenMainScreen(const InitArg& arg);
    ~ForceOpenMainScreen() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
