#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CloseItemMenu : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CloseItemMenu, ksys::act::ai::Action)
public:
    explicit CloseItemMenu(const InitArg& arg);
    ~CloseItemMenu() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
