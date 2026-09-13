#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetupGetDemoModeNumUi : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetupGetDemoModeNumUi, ksys::act::ai::Action)
public:
    explicit SetupGetDemoModeNumUi(const InitArg& arg);
    ~SetupGetDemoModeNumUi() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mNumUiType_d{};
    // dynamic_param at offset 0x28
    int* mAddNum_d{};
};

}  // namespace uking::action
