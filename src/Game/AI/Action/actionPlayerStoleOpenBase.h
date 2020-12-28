#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerStoleOpenBase : public ActionEx {
    SEAD_RTTI_OVERRIDE(PlayerStoleOpenBase, ActionEx)
public:
    explicit PlayerStoleOpenBase(const InitArg& arg);
    ~PlayerStoleOpenBase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const char* mBoneName_s{};
    // static_param at offset 0x28
    const sead::Vector3f* mPosOffset_s{};
    // static_param at offset 0x30
    const sead::Vector3f* mRotOffsetXyz_s{};
};

}  // namespace uking::action
