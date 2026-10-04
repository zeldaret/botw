#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTurnToPosition : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTurnToPosition, ksys::act::ai::Action)
public:
    explicit NPCTurnToPosition(const InitArg& arg);
    ~NPCTurnToPosition() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mPosX_d{};
    // dynamic_param at offset 0x28
    float* mPosY_d{};
    // dynamic_param at offset 0x30
    float* mPosZ_d{};
};

}  // namespace uking::action
