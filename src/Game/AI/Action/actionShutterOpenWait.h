#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShutterOpenWait : public ActionEx {
    SEAD_RTTI_OVERRIDE(ShutterOpenWait, ActionEx)
public:
    explicit ShutterOpenWait(const InitArg& arg);
    ~ShutterOpenWait() override;

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
};

}  // namespace uking::action
