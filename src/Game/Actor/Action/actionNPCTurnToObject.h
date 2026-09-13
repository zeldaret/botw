#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTurnToObject : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTurnToObject, ksys::act::ai::Action)
public:
    explicit NPCTurnToObject(const InitArg& arg);
    ~NPCTurnToObject() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mObjectId_d{};
    // dynamic_param at offset 0x28
    float* mTurnDirection_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mActorName_d{};
};

}  // namespace uking::action
