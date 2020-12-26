#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShutterClose : public ActionEx {
    SEAD_RTTI_OVERRIDE(ShutterClose, ActionEx)
public:
    explicit ShutterClose(const InitArg& arg);
    ~ShutterClose() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mASName_s{};
    // map_unit_param at offset 0x30
    const int* mMoveAxis_m{};
    // map_unit_param at offset 0x38
    const float* mMoveDis_m{};
    // map_unit_param at offset 0x40
    const float* mMoveSpeed_m{};
};

}  // namespace uking::action
