#pragma once

#include "Game/AI/Action/actionSystemHide.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SystemHideChase : public SystemHide {
    SEAD_RTTI_OVERRIDE(SystemHideChase, SystemHide)
public:
    explicit SystemHideChase(const InitArg& arg);
    ~SystemHideChase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
