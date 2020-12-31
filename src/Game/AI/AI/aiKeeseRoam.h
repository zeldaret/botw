#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeeseRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KeeseRoam, ksys::act::ai::Ai)
public:
    explicit KeeseRoam(const InitArg& arg);
    ~KeeseRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mMinOffsetY_s{};
    // static_param at offset 0x40
    const float* mMaxOffsetY_s{};
    // static_param at offset 0x48
    const float* mRoamRadius_s{};
    // static_param at offset 0x50
    const float* mMinMoveDist_s{};
    // static_param at offset 0x58
    const float* mMaxMoveDist_s{};
    // static_param at offset 0x60
    const float* mNoWaitRatio_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mCentralPos_d{};
};

}  // namespace uking::ai
