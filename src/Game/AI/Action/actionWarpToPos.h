#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpToPos : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpToPos, ksys::act::ai::Action)
public:
    explicit WarpToPos(const InitArg& arg);
    ~WarpToPos() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mTargetRot_d{};
};

}  // namespace uking::action
