#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCKnockBackMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCKnockBackMove, ksys::act::ai::Action)
public:
    explicit NPCKnockBackMove(const InitArg& arg);
    ~NPCKnockBackMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mASKeyName_s{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mMoveDir_d{};
};

}  // namespace uking::action
