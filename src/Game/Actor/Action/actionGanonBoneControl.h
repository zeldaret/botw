#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonBoneControl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GanonBoneControl, ksys::act::ai::Action)
public:
    explicit GanonBoneControl(const InitArg& arg);
    ~GanonBoneControl() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mIsBattleModeOn_d{};
};

}  // namespace uking::action
