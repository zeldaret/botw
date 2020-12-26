#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShutterOpen : public ActionEx {
    SEAD_RTTI_OVERRIDE(ShutterOpen, ActionEx)
public:
    explicit ShutterOpen(const InitArg& arg);
    ~ShutterOpen() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mOnLink_s{};
    // static_param at offset 0x28
    const bool* mIsPreOpen_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // map_unit_param at offset 0x40
    const int* mMoveAxis_m{};
    // map_unit_param at offset 0x48
    const float* mMoveDis_m{};
    // map_unit_param at offset 0x50
    const float* mMoveSpeed_m{};
};

}  // namespace uking::action
