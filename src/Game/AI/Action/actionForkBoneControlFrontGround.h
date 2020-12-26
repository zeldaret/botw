#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkBoneControlFrontGround : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkBoneControlFrontGround, ksys::act::ai::Action)
public:
    explicit ForkBoneControlFrontGround(const InitArg& arg);
    ~ForkBoneControlFrontGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const sead::Vector3f* mTargetOffset_s{};
};

}  // namespace uking::action
