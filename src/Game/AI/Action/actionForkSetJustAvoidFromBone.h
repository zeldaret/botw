#pragma once

#include "Game/AI/Action/actionForkSetJustAvoid.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSetJustAvoidFromBone : public ForkSetJustAvoid {
    SEAD_RTTI_OVERRIDE(ForkSetJustAvoidFromBone, ForkSetJustAvoid)
public:
    explicit ForkSetJustAvoidFromBone(const InitArg& arg);
    ~ForkSetJustAvoidFromBone() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x68
    sead::SafeString mTransBaseBoneName_s{};
    // static_param at offset 0x78
    sead::SafeString mRotBaseBoneName_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mBaseDir_s{};
};

}  // namespace uking::action
