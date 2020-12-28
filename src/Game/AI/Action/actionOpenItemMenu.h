#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenItemMenu : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OpenItemMenu, ksys::act::ai::Action)
public:
    explicit OpenItemMenu(const InitArg& arg);
    ~OpenItemMenu() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mMenuType_d{};
};

}  // namespace uking::action
