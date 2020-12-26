#pragma once

#include "Game/AI/Action/actionFreeze.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RagdollFreeze : public Freeze {
    SEAD_RTTI_OVERRIDE(RagdollFreeze, Freeze)
public:
    explicit RagdollFreeze(const InitArg& arg);
    ~RagdollFreeze() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const sead::Vector3f* mDownFrontCtrlOffset_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mDownBackCtrlOffset_s{};
};

}  // namespace uking::action
